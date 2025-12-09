#include "bindings.h"
#include "./h/keyboard.h"

void bind_keyboard(pybind11::module_& m) {
	pybind11::class_<keyboard>(m, "keyboard");
}