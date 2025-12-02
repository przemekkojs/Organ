#pragma once

#include "./lib/RtMidi.h"

#include <string>
#include <vector>

struct MIDI_packet {
	MIDI_packet(unsigned char status, unsigned char note, unsigned char velocity) {
		this->status = status;
		this->note = note;
		this->velocity = velocity;
	}

	unsigned char status;
	unsigned char note;
	unsigned char velocity;
};

class MIDI_controller {
public:
	MIDI_controller(int portNumber, std::string deviceName);
	MIDI_controller(int portNumber, std::string deviceName, bool in, bool out);
	~MIDI_controller();

	std::string getDeviceName();
	int getPortNumber() const;	
	bool acceptsIn() const;
	bool sendsOut() const;

	void setIn(bool in);
	void setOut(bool out);

	void sendMessage(MIDI_packet& msg);

	MIDI_packet readMessage();

private:
	int portNumber;
	bool in;
	bool out;
	std::string deviceName;
	RtMidiIn midiIn;
	RtMidiOut midiOut;	
};