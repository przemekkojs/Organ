#pragma once

#include <pybind11/pybind11.h>

void bind_app(pybind11::module_ &m);
void bind_combinations(pybind11::module_& m);
void bind_keyboard(pybind11::module_& m);
void bind_MIDI_controller(pybind11::module_& m);
void bind_organ(pybind11::module_& m);
void bind_section(pybind11::module_& m);
void bind_voice(pybind11::module_& m);
void bind_voice_group(pybind11::module_& m);
void bind_piston_system(pybind11::module_& m);
void bind_piston(pybind11::module_& m);