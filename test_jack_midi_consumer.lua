require "seqpp"

jmc = seqpp.jack_midi_consumer("test")

time = jmc:time()

for i = 1, 10 do
	jmc:post_event(time + i * 48000, seqpp.midi_event(), true)
end

jmc:drain()

