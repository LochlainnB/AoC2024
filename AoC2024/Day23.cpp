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

struct Computer {
	std::string identifier;
	std::map<std::string, Computer*> connections;

	std::vector<std::string> getLargestNetwork(int targetSize) {
		std::vector<std::string> result;
		for (int i = targetSize; i > 0; i--) {
			std::vector<std::map<std::string, Computer*>::iterator> iterators;
			result = recursiveThing(connections.begin(), i - 1, iterators);
			if (result.size() > 0) {
				result.insert(result.begin(), identifier);
				return result;
			}
		}
		return result;
	}

	std::vector<std::string> recursiveThing(std::map<std::string, Computer*>::iterator start, int remainingLevels, std::vector<std::map<std::string, Computer*>::iterator>& iterators) {
		for (auto it = start; it != connections.end(); it++) {
			bool inNetwork = true;
			for (auto higherIt : iterators) {
				if (!higherIt->second->connections.count(it->first)) {
					inNetwork = false;
				}
			}
			if (inNetwork) {
				if (remainingLevels == 0) {
					std::vector<std::string> result;
					for (auto higherIt : iterators) {
						result.push_back(higherIt->first);
					}
					result.push_back(it->first);
					return result;
				}
				else {
					auto nextIt = it;
					nextIt++;
					iterators.push_back(it);
					std::vector<std::string> result = recursiveThing(nextIt, remainingLevels - 1, iterators);
					iterators.erase(iterators.end() - 1);
					if (result.size() > 0) return result;
				}
			}
		}
		return {};
	}
};

struct SortName {
	bool operator()(const Computer* lhs, const Computer* rhs) {
		return lhs->identifier < rhs->identifier;
	}
};

struct SortSize {
	bool operator()(const Computer* lhs, const Computer* rhs) {
		return lhs->connections.size() > rhs->connections.size();
	}
};

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	// Use lines for 1D vector
	std::vector<std::string> lines = Utils::split(rawInput, "\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> input;
	for (int i = 0; i < lines.size(); i++) {
		input.push_back(Utils::split(lines[i], "-"));
	}

	// Part 1
	std::map<std::string, Computer*> computers;
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].size(); j++) {
			if (!computers.count(input[i][j])) {
				computers[input[i][j]] = new Computer{ input[i][j] };
			}
		}
		computers[input[i][0]]->connections[input[i][1]] = computers[input[i][1]];
		computers[input[i][1]]->connections[input[i][0]] = computers[input[i][0]];
	}

	long long total = 0;
	for (auto it1 = computers.begin(); it1 != computers.end(); it1++) {
		for (auto it2 = it1; it2 != computers.end(); it2++) {
			for (auto it3 = it2; it3 != computers.end(); it3++) {
				if (it1->second->connections.count(it2->first)
				&& it1->second->connections.count(it3->first)
				&& it2->second->connections.count(it3->first)
				&& (it1->first[0] == 't' || it2->first[0] == 't' || it3->first[0] == 't')) {
					total++;
				}
			}
		}
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2

	std::vector<Computer*> computersSorted;
	for (auto it = computers.begin(); it != computers.end(); it++) {
		computersSorted.push_back(it->second);
	}
	std::sort(computersSorted.begin(), computersSorted.end(), SortSize());

	std::vector<std::string> lanNetwork;
	for (int i = 0; i < computersSorted.size(); i++) {
		if (lanNetwork.size() >= computersSorted[i]->connections.size()) {
			break;
		}
		std::vector<std::string> candidateNetwork = computersSorted[i]->getLargestNetwork(computersSorted[i]->connections.size());
		if (candidateNetwork.size() > lanNetwork.size()) {
			lanNetwork = candidateNetwork;
		}
	}

	std::string password = "";
	for (int i = 0; i < lanNetwork.size(); i++) {
		password += lanNetwork[i] + ",";
	}
	password.erase(password.begin() + password.size() - 1);

	std::cout << "Part 2: " << password << "\n";
	Utils::copy(password);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}