require "seqpp"

-- h = seqpp.heap:get_instance()

jmc = seqpp.jack_midi_consumer("test")

e = seqpp.midi_event()

time = jmc:time()

for i = 1, 2000 do
	jmc:post_event(jmc:time() + i * 48000, seqpp.midi_event(), true)
end
