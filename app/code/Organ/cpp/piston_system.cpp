#include "./h/piston_system.h"

pistonSystem::pistonSystem(int portNumber, std::string deviceName) : pistonSystem(portNumber, deviceName, false, true) { }
pistonSystem::pistonSystem(int portNumber, std::string deviceName, bool in, bool out) : MIDI_controller(portNumber, deviceName, in, out), pistons() { }
pistonSystem::~pistonSystem() { }

const std::vector<std::unique_ptr<piston>>& pistonSystem::getPistons() const { return this->pistons; }
void pistonSystem::addPiston(int midiNote, void* callbackFunction) { this->addPiston(new piston(midiNote, callbackFunction)); }
void pistonSystem::removePiston(piston* p) { this->removePiston(p->getMidiNote()); }

void pistonSystem::addPiston(piston* p) {
    int midiNote = p->getMidiNote();
    void* callback = p->getCallbackFunction();

    for (auto it = this->pistons.begin(); it != this->pistons.end(); it++) {
        if ((*it)->getMidiNote() == midiNote) {
            throw new std::exception("Nie można dodać 2 pistonów o tym samym identyfikatorze MIDI");
        }
    }
    
    this->pistons.push_back(std::make_unique<piston>(midiNote, callback));
}

void pistonSystem::removePiston(int midiNote) {
    for (auto it = this->pistons.begin(); it != this->pistons.end(); it++) {
        if ((*it)->getMidiNote() == midiNote) {
            this->pistons.erase(it);
            return;
        }
    }
}

piston::piston(int midiNote, void* callbackFunction) {
    this->midiNote = midiNote;
    this->callbackFunction = callbackFunction;
}

piston::~piston() { }
void piston::press() { }
int piston::getMidiNote() const { return this->midiNote; }
void* piston::getCallbackFunction() const { return this->callbackFunction; }

void switchVoice(voice& v) {
    v.voiceSwitch();
}

void switchVoiceGroup(voiceGroup& vGroup) {
    vGroup.groupSwitch();
}