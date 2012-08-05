#ifndef SEQPP_JACK_CLIENT_HH
#define SEQPP_JACK_CLIENT_HH

#include <jack/jack.h>
#include <jack/midiport.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::runtime_error;
using std::vector;



namespace seqpp {

extern "C" int jack_client_process(jack_nframes_t nframes, void *arg);

struct jack_client {
	jack_client_t *client;

	vector<jack_port_t*> midi_in_ports;
	vector<jack_port_t*> midi_out_ports;

	vector<jack_port_t*> audio_in_ports;
	vector<jack_port_t*> audio_out_ports;

	jack_client(
		const string name,
		vector<string> midi_in_port_names,
		vector<string> midi_out_port_names,
		vector<string> audio_in_port_names,
		vector<string> audio_out_port_names
	) 
		throw (runtime_error) 
	{
		jack_status_t jack_status;

		client = jack_client_open(name.c_str(), JackNullOption, &jack_status);

		if (0 == client) {
			throw runtime_error("failed to open jack client");
		}

		for (unsigned int index = 0; index < midi_in_port_names.size(); ++index) {
			cout << "registering port: " << midi_in_port_names[index] << std::endl;
			jack_port_t *port = jack_port_register(client, midi_in_port_names[index].c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsTerminal | JackPortIsInput, 0);
			midi_in_ports.push_back(port);
		}

		for (unsigned int index = 0; index < midi_out_port_names.size(); ++index) {
			cout << "registering port: " << midi_out_port_names[index] << std::endl;
			jack_port_t *port = jack_port_register(client, midi_out_port_names[index].c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsTerminal | JackPortIsOutput, 0);
			midi_out_ports.push_back(port);
		}

		for (unsigned int index = 0; index < audio_in_port_names.size(); ++index) {
			cout << "registering port: " << audio_in_port_names[index] << std::endl;
			jack_port_t *port = jack_port_register(client, audio_in_port_names[index].c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsTerminal | JackPortIsInput, 0);
			audio_in_ports.push_back(port);
		}

		for (unsigned int index = 0; index < audio_out_port_names.size(); ++index) {
			cout << "registering port: " << audio_out_port_names[index] << std::endl;
			jack_port_t *port = jack_port_register(client, audio_out_port_names[index].c_str(), JACK_DEFAULT_AUDIO_TYPE, JackPortIsTerminal | JackPortIsOutput, 0);
			audio_out_ports.push_back(port);
		}


		jack_set_process_callback(client, seqpp::jack_client_process, (void*)this);

		jack_activate(client);
	}

	virtual ~jack_client() {
		jack_deactivate(client);

		for (unsigned int index = 0; index < midi_in_ports.size(); ++index) {
			jack_port_unregister(client, midi_in_ports[index]);
		}

		for (unsigned int index = 0; index < midi_out_ports.size(); ++index) {
			jack_port_unregister(client, midi_out_ports[index]);
		}

		for (unsigned int index = 0; index < audio_in_ports.size(); ++index) {
			jack_port_unregister(client, audio_in_ports[index]);
		}

		for (unsigned int index = 0; index < audio_out_ports.size(); ++index) {
			jack_port_unregister(client, audio_out_ports[index]);
		}

		jack_client_close(client);
	}

	int do_process(jack_nframes_t nframes) {
		for (unsigned int index = 0; index < midi_out_ports.size(); ++index) {
			jack_midi_clear_buffer(jack_port_get_buffer(midi_out_ports[index], nframes));
		}

		process(nframes);
	}

	virtual int process(jack_nframes_t nframes) = 0;
};

extern "C" int jack_client_process(jack_nframes_t nframes, void *arg) {
	return ((jack_client*)arg)->do_process(nframes);	
}

} // namespace


#endif

