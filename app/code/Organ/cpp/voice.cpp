#include "h/voice.h"

voice::voice(int id, std::string name) {
	this->name = name;
	this->id = id;
	this->on = false;
}

voice::voice() : voice(-1, "G³os") { }

std::string voice::getName() const { return this->name; }
int voice::getId() const { return this->id; }
bool voice::isOn() const { return this->on; }

void voice::voiceOn() { this->on = true; }
void voice::voiceOff() { this->on = false; }
void voice::voiceSwitch() { this->on = !this->on; }