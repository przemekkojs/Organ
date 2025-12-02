#pragma once

#include "h/MIDI_controller.h"
#include "h/section.h"

class keyboard {
public:
	keyboard();
	keyboard(MIDI_controller* device, section* section);	
	~keyboard();

	section* getSection();
	MIDI_controller* getDevice();

	void setDevice(MIDI_controller* device);
	void setSection(section* sect);

private:
	section* sect;
	MIDI_controller* device;
};