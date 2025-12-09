#include "h/organ.h"

organ::organ() : organ(0) { }

organ::organ(int keyboardCount) : keyboards() {
    keyboards.reserve(keyboardCount);

    for (int i = 0; i < keyboardCount; i++) {
        addKeyboard();
    }
}

organ::~organ() {
    delete this->pSystem;
}

void organ::addKeyboard() {
    keyboards.push_back(std::unique_ptr<keyboard>(new keyboard(this->getKeyboardCount())));
}

void organ::addKeyboard(MIDI_controller* device, section* sect) {
    keyboards.push_back(std::unique_ptr<keyboard>(new keyboard(this->getKeyboardCount(), device, sect)));

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
pistonSystem* organ::getPistonSystem() const { return this->pSystem; }

int organ::getKeyboardCount() const { return static_cast<int>(keyboards.size()); }
int organ::getSectionCount() const { return static_cast<int>(sections.size()); }
int organ::getVoiceGroupCount() const { return static_cast<int>(voiceGroups.size()); }

section* organ::getSection(int id) const {
    for (auto& sPtr : this->sections) {
        auto s = sPtr.get();

        if (s->getId() == id) {
            return s;
        }
    }

    return nullptr;
}

keyboard* organ::getKeyboard(int id) const {
    for (auto& kPtr : this->keyboards) {
        auto k = kPtr.get();

        if (k->getId() == id) {
            return k;
        }
    }

    return nullptr;
}

voiceGroup* organ::getVoiceGroup(int id) const {
    for (auto& vgPtr : this->voiceGroups) {
        auto vg = vgPtr.get();

        if (vg->getId() == id) {
            return vg;
        }
    }

    return nullptr;
}