#pragma once
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include <array>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>

std::unordered_map<std::string, std::set<std::string>> keyBeforeValue;
std::unordered_map<std::string, std::set<std::string>> keyAfterValue;

struct sortUpdate {
	bool operator() (const std::string& lhs, const std::string& rhs) {
		return keyBeforeValue[rhs].count(lhs) == 0 && keyAfterValue[lhs].count(rhs) == 0;
	}
};

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	// Split into the two input types
	std::vector<std::string> inputs = Utils::split(rawInput, "\n\n");

	std::vector<std::string> ruleLines = Utils::split(inputs[0], "\n");
	std::vector<std::string> updateLines = Utils::split(inputs[1], "\n");
	
	std::vector<std::vector<std::string>> rules;
	for (int i = 0; i < ruleLines.size(); i++) {
		rules.push_back(Utils::split(ruleLines[i], "|"));
	}
	std::vector<std::vector<std::string>> updates;
	for (int i = 0; i < updateLines.size(); i++) {
		updates.push_back(Utils::split(updateLines[i], ","));
	}

	// Part 1
	for (int i = 0; i < rules.size(); i++) {
		keyBeforeValue[rules[i][0]].insert(rules[i][1]);
		keyAfterValue[rules[i][1]].insert(rules[i][0]);
	}

	int total = 0;
	std::vector<std::vector<std::string>> incorrectUpdates; // Part 2
	for (int i = 0; i < updates.size(); i++) {
		bool valid = true;
		for (int j = 0; j < updates[i].size(); j++) {
			// Look backwards
			for (int k = j - 1; k >= 0; k--) {
				if (keyBeforeValue[updates[i][j]].count(updates[i][k])) {
					valid = false;
					break;
				}
			}
			// Look fowards
			for (int k = j + 1; k < updates[i].size(); k++) {
				if (keyAfterValue[updates[i][j]].count(updates[i][k])) {
					valid = false;
					break;
				}
			}
		}
		if (valid) {
			total += std::stoi(updates[i][updates[i].size() / 2]);
		}
		else {
			incorrectUpdates.push_back(updates[i]); // Part 2
		}
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2
	total = 0;
	for (int i = 0; i < incorrectUpdates.size(); i++) {
		std::sort(incorrectUpdates[i].begin(), incorrectUpdates[i].end(), sortUpdate());
		total += std::stoi(incorrectUpdates[i][incorrectUpdates[i].size() / 2]);
	}
	std::cout << "Part 2: " << total << "\n";
	Utils::copy(total);

	keyBeforeValue.clear();
	keyAfterValue.clear();
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}