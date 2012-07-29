require "libseqpp"

jmc = libseqpp.jack_midi_consumer()

e = libseqpp.midi_event()

jmc:post_event(0, e, false)

