#ifndef SEQPP_MIDI_EVENT_HH
#define SEQPP_MIDI_EVENT_HH

#include <iostream>
#include <vector>

using std::vector;

namespace seqpp {

struct midi_event {
	vector<unsigned char> msg;

	midi_event(vector<unsigned char> msg) : msg(msg) { }

	~midi_event() {
		// std::cout << "~midi_event()" << std::endl;
	}

	static midi_event note_on(unsigned int note, unsigned int velocity) {
		vector<unsigned char> data(3);
		data[0] = 0x90;
		data[1] = note;
		data[2] = velocity;
		return midi_event(data);
	}
};

} // namespace

#endif

