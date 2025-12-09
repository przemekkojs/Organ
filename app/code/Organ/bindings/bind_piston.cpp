#include "bindings.h"
#include "./h/piston_system.h"

void bind_piston(pybind11::module_& m) {
	pybind11::class_<piston>(m, "piston");
}