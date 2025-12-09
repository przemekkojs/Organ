#include "h/section.h"

section::section(int id, const std::string& name, const std::vector<std::shared_ptr<voice>>& voices) : voices(voices) {
    this->name = name;
    this->id = id;
}

section::section(int id, const std::vector<std::shared_ptr<voice>>& voices) : section(id, "Section", voices) { }
section::section(int id, const std::string& name) : section(id, name, {}) { }
section::section() : section(0, "Section", std::vector<std::shared_ptr<voice>>()) { }

std::string section::getName() const { return this->name; }
int section::getVoicesCount() const { return static_cast<int>(this->voices.size()); }
int section::getId() const { return this->id; }
const std::vector<std::shared_ptr<voice>>& section::getVoices() const { return this->voices; }

void section::addVoice(voice* v) { this->voices.push_back(std::shared_ptr<voice>(v)); }
void section::removeVoice(voice* v) { this->removeVoice(v->getId()); }

void section::removeVoice(int vId) {
    for (auto it = voices.begin(); it != voices.end(); ++it) {
        if (it->get()->getId() == vId) {
            voices.erase(it);
            return;
        }
    }
}