#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

struct combination {
	combination(int id) : voiceIds() {
		this->id = id;
	}

	int id;
	std::vector<int> voiceIds;
};

class combinationBank {
public:
	combinationBank(std::string& name);

	void addCombination(int id);
	void removeCombination(int id);

private:
	std::string name;
	std::map<int, std::unique_ptr<combination>> combinations;
};