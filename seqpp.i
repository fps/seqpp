%module seqpp
%{
        #include "midi_event.h"
        #include "consumer.h"
        #include "jack_midi_consumer.h"
        #include <boost/shared_ptr.hpp>

        using namespace seqpp;
%}

%apply unsigned long long { jack_nframes_t }

%include "std_string.i"
%include "std_pair.i"

%include "midi_event.h"
%import "consumer.h"
%template (jmc) seqpp::consumer<jack_nframes_t, midi_event>;
%include "jack_midi_consumer.h"
 
using namespace seqpp;


//namespace std {
//  %template (sequence_vector) vector<seqpp::sequence>;
//  %template (event_vector) vector<seqpp::event*>;
//}

//%template (gc_sequence) seqpp::disposable<seqpp::sequence>;
