#pragma once

#include <string>
#include <vector>
#include <memory>
#include "h/voice.h"

class section {
public:
    section();
    section(const std::string& name);
    section(const std::vector<std::shared_ptr<voice>>& voices);
    section(const std::string& name, const std::vector<std::shared_ptr<voice>>& voices);

    std::string getName() const;
    const std::vector<std::shared_ptr<voice>>& getVoices() const;
    int getVoicesCount() const;

private:
    std::string name;
    std::vector<std::shared_ptr<voice>> voices;
};
