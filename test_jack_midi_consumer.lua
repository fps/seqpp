require "seqpp"

jmc = seqpp.jack_midi_consumer("test")

e = seqpp.midi_event()

jmc:post_event(0, e, false)

