#include "h/combinations.h"

#include <algorithm>

combinationBank::combinationBank(std::string& name) : combinations() { this->name = name; }

void combinationBank::addCombination(int id) {
    if (combinations.find(id) != combinations.end())
        return;

    auto comb = std::make_unique<combination>();
    comb->id = id;

    combinations[id] = std::move(comb);
}

void combinationBank::removeCombination(int id) {
    auto it = combinations.find(id);

    if (it == combinations.end())
        return;

    combinations.erase(it);

    std::vector<int> idsToUpdate;

    for (auto& [key, value] : combinations) {
        if (key > id) {
            idsToUpdate.push_back(key);
        }
    }

    for (int oldId : idsToUpdate) {
        auto combPtr = std::move(combinations[oldId]);
        combinations.erase(oldId);
        combPtr->id -= 1;
        combinations[combPtr->id] = std::move(combPtr);
    }
}