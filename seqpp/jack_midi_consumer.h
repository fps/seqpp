#ifndef SEQPP_JACK_MIDI_CONSUMER_HH
#define SEQPP_JACK_MIDI_CONSUMER_HH

#include <consumer.h>
#include <midi_event.h>
#include <jack_consumer.h>
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

namespace seqpp {

struct jack_midi_consumer : 
	jack_consumer<midi_event, jack_midi_consumer>
{
	typedef consumer<jack_nframes_t, midi_event>::disposable_event disposable_event;
	typedef jack_consumer<midi_event, jack_midi_consumer> jack_consumer_type;

	jack_midi_consumer(string name) 
		throw(runtime_error) : 
		jack_consumer(
			name, 
			vector<string>(), 
			vector<string>(1, "out"), 
			vector<string>(), 
			vector<string>()
		) 
	{

	}

	virtual void process_event(jack_consumer_type::disposable_event e, jack_nframes_t nframes, jack_nframes_t frame) {
		cout << "|" << endl;
	}

	virtual jack_nframes_t time() {
		return jack_frame_time(client);
	}
};


} // namespace

#endif

