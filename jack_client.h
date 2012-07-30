#ifndef SEQPP_JACK_CLIENT_HH
#define SEQPP_JACK_CLIENT_HH

#include <jack/jack.h>
#include <string>
#include <stdexcept>

using std::string;
using std::runtime_error;

extern "C" {
	int jack_process(jack_nframes_t, void *arg);
}

namespace seqpp {

struct jack_client {
	jack_client_t *client;

	jack_client(const string name) {
		jack_status_t jack_status;

		client = jack_client_open(name.c_str(), JackNullOption, &jack_status);

		if (0 == client) {
			throw runtime_error("failed to open jack client");
		}

		jack_set_process_callback(client, jack_process, (void*)this);

		jack_activate(client);
	}

	int process(jack_nframes_t nframes) {
		return 0;
	}
};

} // namespace

extern "C" {
	int jack_process(jack_nframes_t nframes, void *arg) {
		return ((seqpp::jack_client*)arg)->process(nframes);
	}
}

#endif

