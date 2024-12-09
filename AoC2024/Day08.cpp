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
	std::unordered_map<char, std::vector<std::pair<int, int>>> frequencies;
	std::set<std::pair<int, int>> antinodes;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			if (lines[y][x] != '.') {
				frequencies[lines[y][x]].push_back({ x, y });
			}
		}
	}

	for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
		std::vector<std::pair<int, int>>& frequency = it->second;
		for (int i = 0; i < frequency.size() - 1; i++) {
			for (int j = i + 1; j < frequency.size(); j++) {
				std::pair<int, int> iToJ = { frequency[j].first - frequency[i].first, frequency[j].second - frequency[i].second };
				antinodes.insert({ frequency[j].first + iToJ.first, frequency[j].second + iToJ.second });
				antinodes.insert({ frequency[i].first - iToJ.first, frequency[i].second - iToJ.second });
			}
		}
	}

	auto it = antinodes.begin();
	while (it != antinodes.end()) {
		if (it->first < 0 || it->first >= lines[0].size() || it->second < 0 || it->second >= lines.size()) {
			it = antinodes.erase(it);
		}
		else {
			it++;
		}
	}

	std::cout << "Part 1: " << antinodes.size() << "\n";
	Utils::copy(antinodes.size());

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