#ifndef SEQPP_JACK_MIDI_CONSUMER_HH
#define SEQPP_JACK_MIDI_CONSUMER_HH

#include <consumer.h>
#include <midi_event.h>
#include <jack/jack.h>
#include <string>

using std::string;

namespace seqpp {

struct jack_midi_consumer : public  consumer<jack_nframes_t, midi_event> {
	jack_client_t *jack_client;

	jack_midi_consumer(string name) {

	}

	int process(jack_nframes_t nframes) {
		return 0;
	}
};

} // namespace

#endif

