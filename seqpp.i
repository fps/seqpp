%module seqpp
%{
        #include "seqpp/midi_event.h"
        #include "seqpp/consumer.h"
        #include "seqpp/jack_consumer.h"
        #include "seqpp/jack_midi_consumer.h"
        #include <boost/shared_ptr.hpp>

        using namespace seqpp;
%}

%apply unsigned long long { jack_nframes_t }

%include "std_string.i"
%include "std_pair.i"

%include "seqpp/midi_event.h"
%include "seqpp/consumer.h"
%template (jc) seqpp::consumer<jack_nframes_t, seqpp::midi_event >;
%include "seqpp/jack_consumer.h"
%template (jmc) seqpp::jack_consumer<seqpp::midi_event, seqpp::jack_midi_consumer >;
%include "seqpp/jack_midi_consumer.h"
 
using namespace seqpp;


//namespace std {
//  %template (sequence_vector) vector<seqpp::sequence>;
//  %template (event_vector) vector<seqpp::event*>;
//}

//%template (gc_sequence) seqpp::disposable<seqpp::sequence>;
