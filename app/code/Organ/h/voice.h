#pragma once

#include <string>

class voice {
public:
	voice();
	voice(int id, std::string name);
	~voice();

	std::string getName() const;
	int getId() const;
	bool isOn() const;

	void voiceOn();
	void voiceOff();
	void voiceSwitch();

private:
	std::string name;
	int id;
	bool on;
};