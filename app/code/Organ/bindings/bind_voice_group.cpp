#include "bindings.h"
#include "./h/voice_group.h"

void bind_voice_group(pybind11::module_& m) {
	pybind11::class_<voiceGroup>(m, "voiceGroup");
}