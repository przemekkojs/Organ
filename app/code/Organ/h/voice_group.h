#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "voice.h"

class voiceGroup {
public:
    voiceGroup();
    voiceGroup(const std::vector<std::shared_ptr<voice>>& voices);

    std::vector<std::shared_ptr<voice>> getVoices() const;
    bool isOn() const;

    void groupOn();
    void groupOff();
    void groupSwitch();
    void addVoice(const std::shared_ptr<voice>& v);
    void removeVoice(const std::shared_ptr<voice>& v);

private:
    std::vector<std::shared_ptr<voice>> voices;
    bool on;
};
