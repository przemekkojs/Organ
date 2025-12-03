#include "bindings.h"

PYBIND11_MODULE(organ, m) {
	bind_app(m);
	bind_combinations(m);
	bind_keyboard(m);
	bind_MIDI_controller(m);
	bind_organ(m);
	bind_section(m);
	bind_voice(m);
	bind_voice_group(m);
}