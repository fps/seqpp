#ifndef SEQPP_JACK_MIDI_CONSUMER_HH
#define SEQPP_JACK_MIDI_CONSUMER_HH

#include <consumer.h>
#include <midi_event.h>
#include <jack/jack.h>
#include <jack_client.h>
#include <string>
#include <iostream>

using std::string;

namespace seqpp {

struct jack_midi_consumer;

struct jack_midi_consumer : 
	public consumer<jack_nframes_t, midi_event>, 
	public jack_client<jack_midi_consumer> 
{
	jack_midi_consumer(string name) : jack_client(name) {

	}

	int process(jack_nframes_t nframes) {
		// std::cout << "." << std::endl;
		return 0;
	}
};

} // namespace

#endif

