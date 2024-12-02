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

bool checkRecord(std::vector<std::string>& record, bool allowDampening) {
	bool increasing = std::stoi(record[0]) - std::stoi(record[1]) < 0;
	bool thisSafe = true;
	for (int i = 1; i < record.size(); i++) {
		int difference = 0;
		if (increasing) {
			difference = std::stoi(record[i]) - std::stoi(record[i - 1]);
		}
		else {
			difference = std::stoi(record[i - 1]) - std::stoi(record[i]);
		}
		if (difference < 1 || difference > 3) {
			if (allowDampening) {
				std::vector<std::string> option1 = record;
				option1.erase(option1.begin() + i - 1);
				std::vector<std::string> option2 = record;
				option2.erase(option2.begin() + i);
				std::vector<std::string> option3 = record;
				option3.erase(option3.begin());
				thisSafe = checkRecord(option1, false) || checkRecord(option2, false) || checkRecord(option3, false);
			}
			else {
				thisSafe = false;
			}
			break;
		}
	}
	return thisSafe;
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
	int safe = 0;
	for (int i = 0; i < input.size(); i++) {
		if (checkRecord(input[i], false)) {
			safe++;
		}
	}
	std::cout << "Part 1: " << safe << "\n";
	Utils::copy(safe);

	// Part 2
	safe = 0;
	for (int i = 0; i < input.size(); i++) {
		if (checkRecord(input[i], true)) {
			safe++;
		}
	}
	std::cout << "Part 2: " << safe << "\n";
	Utils::copy(safe);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}