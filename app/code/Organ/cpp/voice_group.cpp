#include "h/voice_group.h"

voiceGroup::voiceGroup(int id, std::string name) : voiceGroup(id, name, std::vector<std::shared_ptr<voice>>()) { }
voiceGroup::voiceGroup() : voiceGroup(0, "Voice group") {}

voiceGroup::voiceGroup(int id, std::string name, const std::vector<std::shared_ptr<voice>>& voices) : voices(voices) {
    this->on = false;
    this->name = name;
    this->id = id;
}

std::vector<std::shared_ptr<voice>> voiceGroup::getVoices() const { return voices; }
bool voiceGroup::isOn() const { return on; }
int voiceGroup::getId() const { return this->id; }
std::string voiceGroup::getName() const { return this->name; }

void voiceGroup::groupOn() {
    this->on = true;

    for (auto& v : this->voices) {
        v.get()->voiceOn();
    }
}

void voiceGroup::groupOff() {
    this->on = false;

    for (auto& v : this->voices) {
        v.get()->voiceOff();
    }
}

void voiceGroup::groupSwitch() {
    this->on = !this->on;

    for (auto& v : this->voices) {
        v.get()->voiceSwitch();
    }
}

void voiceGroup::addVoice(const std::shared_ptr<voice>& v) { 
    if (std::find(voices.begin(), voices.end(), v) == voices.end())
        voices.push_back(v);
}

void voiceGroup::removeVoice(const std::shared_ptr<voice>& v) { 
    voices.erase(std::remove(voices.begin(), voices.end(), v), voices.end());
}