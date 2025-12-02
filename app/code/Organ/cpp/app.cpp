#include "h/app.h"

std::vector<std::unique_ptr<MIDI_controller>> detectDevices() {
    RtMidiIn midiIn;
    unsigned int ports = midiIn.getPortCount();
    std::vector<std::unique_ptr<MIDI_controller>> controllers;
    controllers.reserve(ports);

    for (unsigned int i = 0; i < ports; i++) {
        std::string name = midiIn.getPortName(i);
        controllers.push_back(std::make_unique<MIDI_controller>(i, name));
    }

    return controllers;
}