%module seqpp
%{
        #include "midi_event.h"
        #include "jack_midi_consumer.h"
        #include <boost/shared_ptr.hpp>

        using namespace seqpp;
%}

%include "std_string.i"
%include "std_vector.i"

%include "midi_event.h"
%include "jack_midi_consumer.h"
 
using namespace seqpp;

%apply unsigned long long { jack_nframes_t }

//namespace std {
//  %template (sequence_vector) vector<seqpp::sequence>;
//  %template (event_vector) vector<seqpp::event*>;
//}

//%template (gc_sequence) seqpp::disposable<seqpp::sequence>;
//%template (jack_midi_consumer) seqpp::consumer<jack_nframes_t, midi_event>;
