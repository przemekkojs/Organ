#include "bindings.h"
#include "./h/organ.h"

void bind_organ(pybind11::module_& m) {
	pybind11::class_<organ>(m, "organ");
}