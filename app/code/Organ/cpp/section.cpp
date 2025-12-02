#include "h/section.h"

section::section(const std::string& name, const std::vector<std::shared_ptr<voice>>& voices) : voices(voices) {
    this->name = name;
}

section::section(const std::vector<std::shared_ptr<voice>>& voices) : section("Section", voices) { }
section::section(const std::string& name) : section(name, std::vector<std::shared_ptr<voice>>()) { }
section::section() : section("Section", std::vector<std::shared_ptr<voice>>()) { }

std::string section::getName() const { return name; }
int section::getVoicesCount() const { return static_cast<int>(voices.size()); }
const std::vector<std::shared_ptr<voice>>& section::getVoices() const { return voices; }
