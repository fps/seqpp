#ifndef SEQPP_JACK_MIDI_CONSUMER_HH
#define SEQPP_JACK_MIDI_CONSUMER_HH

#include <consumer.h>
#include <midi_event.h>
#include <jack/jack.h>
#include <jack_client.h>
#include <string>
#include <iostream>

using std::string;
using std::pair;

namespace seqpp {

template <class jack_event>
struct jack_consumer : 
	public consumer<jack_nframes_t, jack_event>, 
	public jack_client 
{
	//typename consumer<jack_nframes_t, jack_event>::disposable_event disposable_event;
	typedef boost::shared_ptr<pair<jack_nframes_t, jack_event> > disposable_event;
	typedef consumer<jack_nframes_t, jack_event> consumer_type;
	//typedef consumer_type::disposable_event event_type;

	jack_consumer(string name) : 
		jack_client(name) 
	{

	}

	

	virtual int process(jack_nframes_t nframes) {
		jack_nframes_t frame_time = jack_last_frame_time(client);

		for (jack_nframes_t frame = 0; frame < nframes; ++frame) {
			if (consumer_type::events_in.can_read()) {
				// std::cout << "+" << std::endl;
				disposable_event *ev;
				while ((ev = consumer_type::events_in.peek()) != 0 && (*ev)->first <= (frame_time + frame) && consumer_type::events_in.can_read()) {
					std::cout << "-" << std::endl;
					consumer_type::events_in.read();
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

