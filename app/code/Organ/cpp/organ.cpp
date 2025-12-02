#include "h/organ.h"

organ::organ() : organ(0) { }

organ::organ(int keyboardCount)
{
    keyboards.reserve(keyboardCount);

    for (int i = 0; i < keyboardCount; i++) {
        addKeyboard();
    }
}

void organ::addKeyboard() {
    keyboards.push_back(std::make_unique<keyboard>());
}

void organ::addKeyboard(MIDI_controller* device, section* sect) {
    keyboards.push_back(std::make_unique<keyboard>(device, sect));

    if (sect != nullptr) {
        for (auto it = sections.begin(); it != sections.end(); ++it) {
            if (it->get() == sect) {
                return;
            }
        }

        sections.push_back(std::shared_ptr<section>(sect));
    }
}

void organ::removeKeyboard(MIDI_controller* device) {
    for (auto it = keyboards.begin(); it != keyboards.end(); ++it) {
        if ((*it)->getDevice() == device) {
            keyboards.erase(it);
            return;
        }
    }
}

void organ::removeKeyboard(keyboard* k) { removeKeyboard(k->getDevice()); }

void organ::addSection(section* sect) {
    sections.push_back(std::shared_ptr<section>(sect));
}

void organ::removeSection(section* sect) {
    for (auto it = sections.begin(); it != sections.end(); ++it) {
        if (it->get() == sect) {
            sections.erase(it);
            return;
        }
    }
}

void organ::addVoiceGroup(voiceGroup* vGroup) {
    voiceGroups.push_back(std::shared_ptr<voiceGroup>(vGroup));
}

void organ::removeVoiceGroup(voiceGroup* vGroup) {
    for (auto it = voiceGroups.begin(); it != voiceGroups.end(); ++it) {
        if (it->get() == vGroup) {
            voiceGroups.erase(it);
            return;
        }
    }
}

const std::vector<std::unique_ptr<keyboard>>& organ::getKeyboards() const { return keyboards; }
int organ::getKeyboardCount() const { return static_cast<int>(keyboards.size()); }