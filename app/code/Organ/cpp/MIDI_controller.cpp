#include "h/MIDI_controller.h"
#include <iostream>

MIDI_controller::MIDI_controller(int portNumber, std::string deviceName, bool in, bool out) : midiIn(), midiOut() {
	this->portNumber = portNumber;
	this->deviceName = deviceName;
	this->in = in;
	this->out = out;

	if (in)
		this->midiIn.openPort(portNumber);

	if (out)
		this->midiOut.openPort(portNumber);
}

MIDI_controller::MIDI_controller(int portNumber, std::string deviceName) : MIDI_controller(portNumber, deviceName, true, false) {}
MIDI_controller::~MIDI_controller() {}

std::string MIDI_controller::getDeviceName() { return deviceName; }
bool MIDI_controller::acceptsIn() const { return in; }
bool MIDI_controller::sendsOut() const { return out; }
int MIDI_controller::getPortNumber() const { return portNumber; }

void MIDI_controller::setIn(bool in) { this->in = in; }
void MIDI_controller::setOut(bool out) { this->out = out; }

void MIDI_controller::sendMessage(MIDI_packet& msg) {
	std::vector<unsigned char> toSend;
	toSend.push_back(msg.status);
	toSend.push_back(msg.note);
	toSend.push_back(msg.velocity);

	this->midiOut.sendMessage(&toSend);
}

MIDI_packet MIDI_controller::readMessage() {
    std::vector<unsigned char> message;
    double timestamp = this->midiIn.getMessage(&message);

	return message.size() < 3 ?
		MIDI_packet(0, 0, 0) :
		MIDI_packet(message[0], message[1], message[2]);
}
