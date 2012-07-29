#ifndef SEQPP_JACK_MIDI_CONSUMER_HH
#define SEQPP_JACK_MIDI_CONSUMER_HH

#include <consumer.h>
#include <midi_event.h>
#include <jack/jack.h>

namespace seqpp {

struct jack_midi_consumer : public  consumer<jack_nframes_t, midi_event> {

};

} // namespace

#endif

