#include "bindings.h"
#include "./h/section.h"

void bind_section(pybind11::module_& m) {
	pybind11::class_<section>(m, "section");
}