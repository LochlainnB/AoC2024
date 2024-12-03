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
#include <regex>

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
	std::regex expression("mul\\(\\d{1,3},\\d{1,3}\\)");
	std::regex_token_iterator<std::string::iterator> it(rawInput.begin(), rawInput.end(), expression);
	std::vector<std::string> matches;
	while (it != std::regex_token_iterator<std::string::iterator>()) {
		matches.push_back(*it);
		it++;
	}

	int total = 0;
	for (int i = 0; i < matches.size(); i++) {
		matches[i] = matches[i].substr(4, matches[i].size() - 5);
		std::vector<std::string> numbers = Utils::split(matches[i], ",");
		total += std::stoi(numbers[0]) * std::stoi(numbers[1]);
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2
	expression = std::regex("(mul\\(\\d{1,3},\\d{1,3}\\))|(do\\(\\))|(don't\\(\\))");
	it = std::regex_token_iterator<std::string::iterator>(rawInput.begin(), rawInput.end(), expression);
	matches.clear();
	while (it != std::regex_token_iterator<std::string::iterator>()) {
		matches.push_back(*it);
		it++;
	}

	total = 0;
	bool enabled = true;
	for (int i = 0; i < matches.size(); i++) {
		if (matches[i] == "do()") {
			enabled = true;
		}
		else if (matches[i] == "don't()") {
			enabled = false;
		}
		else if (enabled) {
			matches[i] = matches[i].substr(4, matches[i].size() - 5);
			std::vector<std::string> numbers = Utils::split(matches[i], ",");
			total += std::stoi(numbers[0]) * std::stoi(numbers[1]);
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