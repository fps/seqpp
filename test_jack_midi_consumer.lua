require "seqpp"

jmc = seqpp.jack_midi_consumer("test")

time = jmc:time()

for i = 1, 50 do
	jmc:post_event(time + i * 48000, seqpp.midi_event_note_on(64,80), true)
end

jmc:drain()

