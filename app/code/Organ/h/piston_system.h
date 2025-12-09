#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

#include "h/MIDI_controller.h"
#include "h/voice.h"
#include "h/voice_group.h"

inline void switchVoice(voice& v);
inline void switchVoiceGroup(voiceGroup& vGroup);

class piston {
public:
    piston(int midiNote, std::function<void()> callbackFunction);
    piston(const piston& other);

    void press();

    int getMidiNote() const;
    std::function<void()> getCallbackFunction() const;

private:
    int midiNote;
    std::function<void()> callbackFunction;
};

class pistonSystem : MIDI_controller {
public:
    pistonSystem(int portNumber, std::string deviceName);
    pistonSystem(int portNumber, std::string deviceName, bool in, bool out);

    const std::vector<std::unique_ptr<piston>>& getPistons() const;
    void addPiston(piston* p);
    void addPiston(int midiNote, std::function<void()> callbackFunction);

    void removePiston(piston* p);
    void removePiston(int midiNote);

private:
    std::vector<std::unique_ptr<piston>> pistons;
};