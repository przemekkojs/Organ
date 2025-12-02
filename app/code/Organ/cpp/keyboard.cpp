#include "h/keyboard.h"

keyboard::keyboard(MIDI_controller* device, section* section) {
	this->sect = section;
	this->device = device;
}

keyboard::keyboard() : keyboard(nullptr, nullptr) {}
keyboard::~keyboard() {}

section* keyboard::getSection() { return sect; }
MIDI_controller* keyboard::getDevice() { return device; }
void keyboard::setDevice(MIDI_controller* device) { this->device = device; }
void keyboard::setSection(section* sect) { this->sect = sect; }