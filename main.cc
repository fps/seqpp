#include <jack_midi_consumer.h>
#include <unistd.h>

int main() {
	seqpp::jack_midi_consumer c("test");

	seqpp::midi_event e;

	c.post_event(0, e, true);

	usleep(10000000);
}
