#pragma once

#include <string>
#include <vector>
#include <memory>
#include "h/voice.h"

class section {
public:
    section();
    section(int id, const std::string& name);
    section(int id, const std::vector<std::shared_ptr<voice>>& voices);
    section(int id, const std::string& name, const std::vector<std::shared_ptr<voice>>& voices);

    std::string getName() const;
    const std::vector<std::shared_ptr<voice>>& getVoices() const;
    int getVoicesCount() const;
    int getId() const;

    void addVoice(voice* v);
    void removeVoice(voice* v);
    void removeVoice(int vId);

private:
    int id;
    std::string name;
    std::vector<std::shared_ptr<voice>> voices;
};
