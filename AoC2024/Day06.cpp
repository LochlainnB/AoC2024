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

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	// Use lines for 1D vector
	std::vector<std::string> lines = Utils::split(rawInput, "\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> input;
	for (int i = 0; i < lines.size(); i++) {
		input.push_back(Utils::split(lines[i], " "));
	}

	// Part 1
	std::set<std::pair<int, int>> visited;
	std::pair<int, int> position;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			if (lines[y][x] == '^') {
				position = { x, y };
				x = lines[y].size() - 1;
				y = lines.size() - 1;
			}
		}
	}

	int direction = 0;
	while (position.first >= 0 && position.first < lines[0].size() && position.second >= 0 && position.second < lines.size()) {
		visited.insert(position);
		switch (direction) {
		case 0:
			if (position.second <= 0 || lines[position.second - 1][position.first] != '#') {
				position.second--;
			}
			else direction = (direction + 1) % 4;
			break;
		case 1:
			if (position.first >= lines[0].size() - 1 || lines[position.second][position.first + 1] != '#') {
				position.first++;
			}
			else direction = (direction + 1) % 4;
			break;
		case 2:
			if (position.second >= lines.size() - 1 || lines[position.second + 1][position.first] != '#') {
				position.second++;
			}
			else direction = (direction + 1) % 4;
			break;
		case 3:
			if (position.first <= 0 || lines[position.second][position.first - 1] != '#') {
				position.first--;
			}
			else direction = (direction + 1) % 4;
			break;
		}
	}

	std::cout << "Part 1: " << visited.size() << "\n";
	Utils::copy(visited.size());

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