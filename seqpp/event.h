#ifndef SEQPP_EVENT_HH
#define SEQPP_EVENT_HH

namespace seqpp {

/*
	An event is something that can be consumed by something
	to have some sort of effect (e.g. emit a midi note at 
	a certain time

	How any information is processed depends solely on the
	consumer.
*/
struct event {
	virtual ~event() { }
};

} // namespace

#endif

