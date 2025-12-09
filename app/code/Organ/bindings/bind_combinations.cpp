#include "bindings.h"
#include "./h/combinations.h"

void bind_combinations(pybind11::module_& m) {
	pybind11::class_<combination>(m, "combination");
	pybind11::class_<combinationBank>(m, "combinationBank");
}