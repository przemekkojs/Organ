#include "h/voice_group.h"

voiceGroup::voiceGroup() { this->on = false; }

voiceGroup::voiceGroup(const std::vector<std::shared_ptr<voice>>& voices) : voices(voices) {
    this->on = false;
}

std::vector<std::shared_ptr<voice>> voiceGroup::getVoices() const { return voices; }
bool voiceGroup::isOn() const { return on; }

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