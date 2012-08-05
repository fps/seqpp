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


	static midi_event note_on(unsigned int note, unsigned int velocity, unsigned int channel = 0, bool normalize_note_off = true) {
		if (true == normalize_note_off && velocity == 0) {
			return note_off(note, 128, channel);
		}

		vector<unsigned char> data(3);
		data[0] = 0x90 | channel;
		data[1] = note;
		data[2] = velocity;
		return midi_event(data);
	}

	static midi_event note_off(unsigned int note, unsigned int velocity, unsigned int channel = 0) {
		vector<unsigned char> data(3);
		data[0] = 0x80 | channel;
		data[1] = note;
		data[2] = velocity;
		return midi_event(data);
	}
};

} // namespace

#endif

