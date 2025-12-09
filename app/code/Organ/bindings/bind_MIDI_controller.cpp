#include "bindings.h"
#include "./h/MIDI_controller.h"

void bind_MIDI_controller(pybind11::module_& m) {
	pybind11::class_<MIDI_controller>(m, "MIDI_controller");
}