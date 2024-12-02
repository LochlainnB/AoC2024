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
	int safe = 0;
	for (int i = 0; i < input.size(); i++) {
		bool increasing = std::stoi(input[i][0]) - std::stoi(input[i][1]) < 0;
		bool thisSafe = true;
		for (int j = 1; j < input[i].size(); j++) {
			int difference = 0;
			if (increasing) {
				difference = std::stoi(input[i][j]) - std::stoi(input[i][j - 1]);
			}
			else {
				difference = std::stoi(input[i][j - 1]) - std::stoi(input[i][j]);
			}
			if (difference < 1 || difference > 3) {
				thisSafe = false;
				break;
			}
		}
		if (thisSafe) {
			safe++;
		}
	}
	std::cout << "Part 1: " << safe << "\n";
	Utils::copy(safe);

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