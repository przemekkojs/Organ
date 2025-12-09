#pragma once

#include "h/MIDI_controller.h"
#include "h/section.h"

class keyboard {
public:
	keyboard(int id);
	keyboard(int id, MIDI_controller* device, section* section);	
	~keyboard();

	void setDevice(MIDI_controller* device);
	void setSection(section* sect);

	section* getSection() const;
	MIDI_controller* getDevice() const;
	int getId() const;

private:
	int id;
	section* sect;
	MIDI_controller* device;
};