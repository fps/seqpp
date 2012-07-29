#ifndef SEQPP_JACK_CLIENT_HH
#define SEQPP_JACK_CLIENT_HH

#include <jack/jack.h>
#include <string>

struct jack_client {
	jack_client_t *client;

	jack_client(const string name) {
		client = jack_client_open(name.c_str());
	}

};

extern "C" {
	int process(jack_nframes_t, void *arg) {

	}
}

#endif

