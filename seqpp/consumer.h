#ifndef SEQPP_CONSUMER_HH
#define SEQPP_CONSUMER_HH

#include <ringbuffer.h>
#include <utility>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include <list>
#include <gc.h>

using std::pair;
using std::make_pair;
using std::list;

namespace seqpp {

template<class time_type, class event_type>
struct consumer {
	typedef boost::shared_ptr<pair<time_type, event_type> > disposable_event;

	ringbuffer<disposable_event> events_in;

	consumer() : 
		events_in(1024)
	{  }


	virtual ~consumer() { }

	/*
		Specializations need to implement this in such a way
		that it posts events only if possible. If the block 
		argument is true, block until the event is posted or
		discarded. 

		If the event is not successfully posted,
		return false.
	*/
	virtual bool post_event(const disposable_event e, bool is_blocking = false) {
		if (false == is_blocking && false == events_in.can_write()) {
			return false;
		}

		if (false == is_blocking && true == events_in.can_write()) {
			events_in.write(e);
			return true;
		}

		while (true == is_blocking && false == events_in.can_write()) {
			usleep(10000);	
		}

		garbage.heap.push_back(e);

		events_in.write(e);
		return true;
	}

	virtual bool post_event(const time_type t, const event_type e, bool is_blocking = false) {
		disposable_event ev(new pair<time_type, event_type>(t, e));
		return post_event(ev, is_blocking);
	}

	virtual time_type time() = 0;

	protected:
	gc<disposable_event> garbage;
};

} // namespace

#endif

