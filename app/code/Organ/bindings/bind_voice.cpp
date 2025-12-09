#include "bindings.h"
#include "./h/voice.h"

void bind_voice(pybind11::module_& m) {
    pybind11::class_<voice>(m, "voice");

    // JAKIŒ TAM WZÓR:
    /*pybind11::class_<voice>(m, "voice")
        .def(pybind11::init<>())
        .def(pybind11::init<int, std::string>())
        .def("getName", &voice::getName)
        .def("getId", &voice::getId)
        .def("isOn", &voice::isOn)
        .def("voiceOn", &voice::voiceOn)
        .def("voiceOff", &voice::voiceOff)
        .def("voiceSwitch", &voice::voiceSwitch);*/
}