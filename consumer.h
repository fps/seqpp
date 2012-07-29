#ifndef SEQPP_CONSUMER_HH
#define SEQPP_CONSUMER_HH

#include <ringbuffer.h>
#include <utility>
#include <unistd.h>

using std::pair;
using std::make_pair;

namespace seqpp {

template<class time_type, class event_type>
struct consumer {
	ringbuffer<pair<time_type, event_type> > events;

	consumer() : events(1024) { }

	/*
		Specializations need to implement this in such a way
		that it posts events only if possible. If the block 
		argument is true, block until the event is posted or
		discarded. 

		If the event is not successfully posted,
		return false.
	*/
	bool post_event(const pair<time_type, event_type> e, bool is_blocking = false) {
		if (false == is_blocking && false == events.can_write()) {
			return false;
		}

		if (false == is_blocking && true == events.can_write()) {
			events.write(e);
			return true;
		}

		while (true == is_blocking && false == events.can_write()) {
			usleep(10000);	
		}
		events.write(e);
	}

	bool post_event(const time_type t, const event_type e, bool is_blocking = false) {
		pair<time_type, event_type> p = make_pair(t, e);
		return post_event(p, is_blocking);
	}
};

} // namespace

#endif

