#include "./h/piston_system.h"

pistonSystem::pistonSystem(int portNumber, std::string deviceName) : pistonSystem(portNumber, deviceName, false, true) { }
pistonSystem::pistonSystem(int portNumber, std::string deviceName, bool in, bool out) : MIDI_controller(portNumber, deviceName, in, out), pistons() { }

const std::vector<std::unique_ptr<piston>>& pistonSystem::getPistons() const { return this->pistons; }
void pistonSystem::addPiston(int midiNote, std::function<void()> callbackFunction) { this->addPiston(new piston(midiNote, callbackFunction)); }
void pistonSystem::removePiston(piston* p) { this->removePiston(p->getMidiNote()); }

void pistonSystem::addPiston(piston* p) {
    int midiNote = p->getMidiNote();

    for (auto it = this->pistons.begin(); it != this->pistons.end(); it++) {
        if ((*it)->getMidiNote() == midiNote) {
            throw new std::exception("Nie można dodać 2 pistonów o tym samym identyfikatorze MIDI");
        }
    }
    
    this->pistons.push_back(std::make_unique<piston>(*p));
}

void pistonSystem::removePiston(int midiNote) {
    for (auto it = this->pistons.begin(); it != this->pistons.end(); it++) {
        if ((*it)->getMidiNote() == midiNote) {
            this->pistons.erase(it);
            return;
        }
    }
}

piston::piston(int midiNote, std::function<void()> callbackFunction) : callbackFunction(callbackFunction) {
    this->midiNote = midiNote;
}

piston::piston(const piston& other) : callbackFunction(other.callbackFunction) { 
    this->midiNote = other.midiNote;
}

void piston::press() {
    if (callbackFunction) {
        callbackFunction();
    }
}

int piston::getMidiNote() const { return this->midiNote; }
std::function<void()> piston::getCallbackFunction() const { return this->callbackFunction; }

void switchVoice(voice& v) {
    v.voiceSwitch();
}

void switchVoiceGroup(voiceGroup& vGroup) {
    vGroup.groupSwitch();
}