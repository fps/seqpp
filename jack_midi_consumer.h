#ifndef SEQPP_JACK_MIDI_CONSUMER_HH
#define SEQPP_JACK_MIDI_CONSUMER_HH

#include <consumer.h>
#include <midi_event.h>
#include <jack_consumer.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace seqpp {

struct jack_midi_consumer : 
	jack_consumer<midi_event, jack_midi_consumer>
{
	typedef consumer<jack_nframes_t, midi_event>::disposable_event disposable_event;
	typedef jack_consumer<midi_event, jack_midi_consumer> jack_consumer_type;

	jack_midi_consumer(string name) : 
		jack_consumer(name) 
	{

	}

	virtual void process_event(jack_consumer_type::disposable_event e) {
		cout << "-" << endl;
	}

	virtual jack_nframes_t time() {
		return jack_frame_time(client);
	}
};


} // namespace

#endif

