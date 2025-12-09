#pragma once

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "voice.h"

class voiceGroup {
public:
    voiceGroup();
    voiceGroup(int id, std::string name);
    voiceGroup(int id, std::string name, const std::vector<std::shared_ptr<voice>>& voices);

    std::vector<std::shared_ptr<voice>> getVoices() const;
    bool isOn() const;
    std::string getName() const;
    int getId() const;

    void groupOn();
    void groupOff();
    void groupSwitch();
    void addVoice(const std::shared_ptr<voice>& v);
    void removeVoice(const std::shared_ptr<voice>& v);

private:
    int id;
    std::string name;
    std::vector<std::shared_ptr<voice>> voices;
    bool on;
};
