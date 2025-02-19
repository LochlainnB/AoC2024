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
		input.push_back(Utils::split(lines[i], "   "));
	}

	// Part 1
	std::vector<int> first, second;
	for (int i = 0; i < input.size(); i++) {
		first.push_back(std::stoi(input[i][0]));
		second.push_back(std::stoi(input[i][1]));
	}
	std::sort(first.begin(), first.end());
	std::sort(second.begin(), second.end());

	int total = 0;
	for (int i = 0; i < input.size(); i++) {
		total += max(first[i], second[i]) - min(first[i], second[i]);
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2
	total = 0;
	for (int i = 0; i < input.size(); i++) {
		total += first[i] * std::count(second.begin(), second.end(), first[i]);
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