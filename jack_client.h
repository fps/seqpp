#ifndef SEQPP_JACK_CLIENT_HH
#define SEQPP_JACK_CLIENT_HH

#include <jack/jack.h>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

struct jack_client {
	jack_client_t *client;

	jack_client(const string name) {
		jack_status_t jack_status;
		client = jack_client_open(name.c_str(), JackNullOption, &jack_status);
		if (0 == client) {
			throw runtime_error("failed to open jack client");
		}
	}

};

extern "C" {
	int jack_process(jack_nframes_t, void *arg) {
		return 0;
	}
}

#endif

