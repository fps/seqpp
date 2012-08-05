#ifndef SEQPP_MIDI_CONSUMER_HH
#define SEQPP_MIDI_CONSUMER_HH

#include <consumer.h>
#include <midi_event.h>
#include <jack/jack.h>
#include <jack_client.h>
#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <vector>

using std::string;
using std::pair;
using std::vector;

namespace seqpp {

template <class event_type, class event_processor_type>
struct jack_consumer : 
	public consumer<jack_nframes_t, event_type>, 
	public jack_client 
{
	typedef boost::shared_ptr<pair<jack_nframes_t, event_type> > disposable_event;
	typedef consumer<jack_nframes_t, event_type> consumer_type;

	consumer_type::events_in;

	jack_consumer(string name, vector<string> midi_in_port_names, vector<string> midi_out_port_names, vector<string> audio_in_port_names, vector<string> audio_out_port_names) 
		throw (runtime_error) : 
		jack_client(name, midi_in_port_names, midi_out_port_names, audio_in_port_names, audio_out_port_names)
	{

	}

	virtual ~jack_consumer() {

	}
	
	virtual int process(jack_nframes_t nframes) {
		jack_nframes_t frame_time = jack_last_frame_time(client);

		for (jack_nframes_t frame = 0; frame < nframes; ++frame) {
			if (events_in.can_read()) {
				// std::cout << "+" << std::endl;
				disposable_event *ev;
				while ((ev = events_in.peek()) != 0 && (*ev)->first <= (frame_time + frame) && events_in.can_read()) {
					std::cout << "-" << std::endl;
					disposable_event e = events_in.read();
					static_cast<event_processor_type*>(this)->process_event(e, nframes, frame);
				}
			}
		}
		// std::cout << "." << std::endl;
		return 0;
	}

	virtual jack_nframes_t time() {
		return jack_frame_time(client);
	}
};


} // namespace

#endif

