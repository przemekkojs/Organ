#pragma once

#include <string>
#include <vector>
#include <memory>

#include "h/keyboard.h"
#include "h/section.h"
#include "h/voice_group.h"
#include "h/piston_system.h"

class organ {
public:
    organ();
    organ(int keyboardCount);
    ~organ();

    void addKeyboard();
    void addKeyboard(MIDI_controller* device, section* sect);
    void removeKeyboard(MIDI_controller* device);
    void removeKeyboard(keyboard* k);

    void addSection(section* sect);
    void removeSection(section* sect);

    void addVoiceGroup(voiceGroup* vGroup);
    void removeVoiceGroup(voiceGroup* vGroup);

    const std::vector<std::unique_ptr<keyboard>>& getKeyboards() const;
    
    int getKeyboardCount() const;
    int getSectionCount() const;
    int getVoiceGroupCount() const;

    section* getSection(int id) const;
    keyboard* getKeyboard(int id) const;
    voiceGroup* getVoiceGroup(int id) const;
    pistonSystem* getPistonSystem() const;

private:
    std::vector<std::unique_ptr<keyboard>> keyboards;
    std::vector<std::shared_ptr<section>> sections;
    std::vector<std::shared_ptr<voiceGroup>> voiceGroups;

    pistonSystem* pSystem;
};
