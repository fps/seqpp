#include <jack_midi_consumer.h>

int main() {
	seqpp::jack_midi_consumer c("test");

	seqpp::midi_event e;

	c.post_event(0, e, true);
}
