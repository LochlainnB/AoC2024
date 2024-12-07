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

int getVisited(std::vector<std::string>& map) {
	// Part 1
	std::set<std::pair<int, int>> visited;
	std::set<std::pair<std::pair<int, int>, int>> states;
	std::pair<int, int> position;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == '^') {
				position = { x, y };
				x = map[y].size() - 1;
				y = map.size() - 1;
			}
		}
	}

	int direction = 0;
	while (position.first >= 0 && position.first < map[0].size() && position.second >= 0 && position.second < map.size()) {
		visited.insert(position);
		if (states.count({ position, direction })) {
			return -1;
		}
		states.insert({ position, direction });
		switch (direction) {
		case 0:
			if (position.second <= 0 || map[position.second - 1][position.first] != '#') {
				position.second--;
			}
			else direction = (direction + 1) % 4;
			break;
		case 1:
			if (position.first >= map[0].size() - 1 || map[position.second][position.first + 1] != '#') {
				position.first++;
			}
			else direction = (direction + 1) % 4;
			break;
		case 2:
			if (position.second >= map.size() - 1 || map[position.second + 1][position.first] != '#') {
				position.second++;
			}
			else direction = (direction + 1) % 4;
			break;
		case 3:
			if (position.first <= 0 || map[position.second][position.first - 1] != '#') {
				position.first--;
			}
			else direction = (direction + 1) % 4;
			break;
		}
	}

	return visited.size();
}

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
	int visited = getVisited(lines);

	std::cout << "Part 1: " << visited << "\n";
	Utils::copy(visited);

	// Part 2
	int obstructions = 0;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			if (lines[y][x] == '.') {
				std::vector<std::string> map(lines);
				map[y][x] = '#';
				if (getVisited(map) == -1) {
					obstructions++;
				}
			}
		}
	}
	std::cout << "Part 2: " << obstructions << "\n";
	Utils::copy(obstructions);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}