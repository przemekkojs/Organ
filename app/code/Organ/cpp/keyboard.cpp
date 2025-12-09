#include "h/keyboard.h"

keyboard::keyboard(int id, MIDI_controller* device, section* section) {
	this->sect = section;
	this->device = device;
	this->id = id;
}

keyboard::keyboard(int id) : keyboard(id, nullptr, nullptr) {}
keyboard::~keyboard() {}

section* keyboard::getSection() const { return this->sect; }
MIDI_controller* keyboard::getDevice() const { return this->device; }
int keyboard::getId() const { return this->id; }

void keyboard::setDevice(MIDI_controller* device) { this->device = device; }
void keyboard::setSection(section* sect) { this->sect = sect; }