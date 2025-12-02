#pragma once

#include <vector>

#include "./lib/RtMidi.h"
#include "organ.h"

std::vector<std::unique_ptr<MIDI_controller>> detectDevices();