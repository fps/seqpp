#ifndef SEQPP_JACK_CLIENT_HH
#define SEQPP_JACK_CLIENT_HH

#include <jack/jack.h>
#include <string>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::runtime_error;



namespace seqpp {


template <class client_type>
struct jack_client {
	jack_client_t *client;

	jack_client(const string name) {
		jack_status_t jack_status;

		client = jack_client_open(name.c_str(), JackNullOption, &jack_status);

		if (0 == client) {
			throw runtime_error("failed to open jack client");
		}

		jack_set_process_callback(client, static_process, (void*)this);

		jack_activate(client);
	}

	virtual ~jack_client() {
		jack_deactivate(client);
		jack_client_close(client);
	}

	int process(jack_nframes_t nframes) {
		return static_cast<client_type*>(this)->process(nframes);
	}

	static int static_process(jack_nframes_t nframes, void *arg) {
		return ((jack_client<client_type>*)arg)->process(nframes);
	}
};

} // namespace


#endif

