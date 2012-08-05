#ifndef SEQPP_MIDI_EVENT_HH
#define SEQPP_MIDI_EVENT_HH

#include <iostream>

namespace seqpp {

struct midi_event {
	~midi_event() {
		// std::cout << "~midi_event()" << std::endl;
	}
};

} // namespace

#endif

