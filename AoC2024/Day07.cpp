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
		input.push_back(Utils::split(lines[i], ": "));
	}

	std::vector<std::vector<std::string>> numbers;
	for (int i = 0; i < input.size(); i++) {
		numbers.push_back(Utils::split(input[i][1], " "));
	}

	// Part 1
	long long total = 0;
	for (int i = 0; i < input.size(); i++) {
		int combinations = pow(2, numbers[i].size() - 1);
		for (int combination = 0; combination < combinations; combination++) {
			long long testValue = std::stoi(numbers[i][0]);
			for (int j = 1; j < numbers[i].size(); j++) {
				if (combination >> j - 1 & 1) {
					testValue += std::stoi(numbers[i][j]);
				}
				else {
					testValue *= std::stoi(numbers[i][j]);
				}
			}
			if (testValue == std::stoll(input[i][0])) {
				total += testValue;
				combination = combinations;
			}
		}
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2
	total = 0;
	for (int i = 0; i < input.size(); i++) {
		int combinations = pow(3, numbers[i].size() - 1);
		for (int combination = 0; combination < combinations; combination++) {
			long long testValue = std::stoi(numbers[i][0]);
			for (int j = 1; j < numbers[i].size(); j++) {
				int oprator = combination / int(pow(3, j - 1)) % 3;
				if (oprator == 0) {
					testValue += std::stoi(numbers[i][j]);
				}
				else if (oprator == 1) {
					testValue *= std::stoi(numbers[i][j]);
				}
				else {
					testValue = std::stoll(std::to_string(testValue) + numbers[i][j]);
				}
			}
			if (testValue == std::stoll(input[i][0])) {
				total += testValue;
				combination = combinations;
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