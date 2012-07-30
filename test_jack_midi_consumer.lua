require "seqpp"

-- h = seqpp.heap:get_instance()

jmc = seqpp.jack_midi_consumer("test")

e = seqpp.midi_event()

jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
jmc:post_event(jmc:time() + 48000, seqpp.midi_event(), true)
