#pragma once

#include <string>
#include <vector>
#include <memory>

#include "h/MIDI_controller.h"
#include "h/voice.h"
#include "h/voice_group.h"

void switchVoice(voice& v);
void switchVoiceGroup(voiceGroup& vGroup);

class piston {
public:
    piston(int midiNote, void* callbackFunction);
    ~piston();

    void press();

    int getMidiNote() const;
    void* getCallbackFunction() const;

private:
    int midiNote;
    void* callbackFunction;
};

class pistonSystem : MIDI_controller {
public:
    pistonSystem(int portNumber, std::string deviceName);
    pistonSystem(int portNumber, std::string deviceName, bool in, bool out);
    ~pistonSystem();

    const std::vector<std::unique_ptr<piston>>& getPistons() const;
    void addPiston(piston* p);
    void addPiston(int midiNote, void* callbackFunction);

    void removePiston(piston* p);
    void removePiston(int midiNote);

private:
    std::vector<std::unique_ptr<piston>> pistons;
};