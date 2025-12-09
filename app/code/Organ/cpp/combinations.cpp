#include "h/combinations.h"

#include <algorithm>

combinationBank::combinationBank(std::string name) : combinations() { this->name = name; }

std::string combinationBank::getName() const { return this->name; }
const std::map<int, std::unique_ptr<combination>>& combinationBank::getCombinations() const { return this->combinations;  }

combination* combinationBank::getCombination(int id) const {
    auto it = combinations.find(id);

    if (it == combinations.end())
        return nullptr;

    return it->second.get();
}

void combinationBank::addCombination(int id) {
    if (combinations.find(id) != combinations.end())
        return;

    auto comb = std::make_unique<combination>(id);
    comb->id = id;

    combinations[id] = std::move(comb);
}   

void combinationBank::removeCombination(int id) {
    auto it = combinations.find(id);

    if (it == combinations.end())
        return;

    combinations.erase(it);

    std::vector<int> idsToUpdate;

    for (auto& kv : combinations) {
        auto& key = kv.first;
        auto& val = kv.second;

        if (key > id) {
            idsToUpdate.push_back(key);
        }
    }

    for (int oldId : idsToUpdate) {
        std::unique_ptr<combination> combPtr = std::move(combinations[oldId]);
        combinations.erase(oldId);
        combPtr->id -= 1;
        combinations[combPtr->id] = std::move(combPtr);
    }
}