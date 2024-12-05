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
	int total = 0;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			std::vector<std::string> words;

			// Right
			if (x <= lines[y].size() - 4) {
				words.push_back({ lines[y][x], lines[y][x + 1], lines[y][x + 2], lines[y][x + 3] });
			}
			// Left
			if (x >= 3) {
				words.push_back({ lines[y][x], lines[y][x - 1], lines[y][x - 2], lines[y][x - 3] });
			}
			// Down
			if (y <= lines.size() - 4) {
				words.push_back({ lines[y][x], lines[y + 1][x], lines[y + 2][x], lines[y + 3][x] });
			}
			// Up
			if (y >= 3) {
				words.push_back({ lines[y][x], lines[y - 1][x], lines[y - 2][x], lines[y - 3][x] });
			}
			// Up Right
			if (x <= lines[y].size() - 4 && y >= 3) {
				words.push_back({ lines[y][x], lines[y - 1][x + 1], lines[y - 2][x + 2], lines[y - 3][x + 3] });
			}
			// Down Right
			if (x <= lines[y].size() - 4 && y <= lines.size() - 4) {
				words.push_back({ lines[y][x], lines[y + 1][x + 1], lines[y + 2][x + 2], lines[y + 3][x + 3] });
			}
			// Down Left
			if (x >= 3 && y <= lines.size() - 4) {
				words.push_back({ lines[y][x], lines[y + 1][x - 1], lines[y + 2][x - 2], lines[y + 3][x - 3] });
			}
			// Up Left
			if (x >= 3 && y >= 3) {
				words.push_back({ lines[y][x], lines[y - 1][x - 1], lines[y - 2][x - 2], lines[y - 3][x - 3] });
			}

			for (std::string word : words) {
				if (word == "XMAS") {
					total++;
				}
			}
		}
	}
	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2
	total = 0;
	for (int y = 1; y < lines.size() - 1; y++) {
		for (int x = 1; x < lines[y].size() - 1; x++) {
			if (lines[y][x] == 'A') {
				if ((lines[y - 1][x - 1] == 'M' && lines[y + 1][x + 1] == 'S' || lines[y - 1][x - 1] == 'S' && lines[y + 1][x + 1] == 'M')
					&& (lines[y - 1][x + 1] == 'M' && lines[y + 1][x - 1] == 'S' || lines[y - 1][x + 1] == 'S' && lines[y + 1][x - 1] == 'M')) {
					total++;
				}
			}
		}
	}

	std::cout << "Part 2: " << total << "\n";
	Utils::copy(total);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}