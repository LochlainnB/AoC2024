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

	//std::cout << "Part 2: " <<  << "\n";
	//Utils::copy();
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}