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

struct Stone {
	long long value;

	void blink(std::vector<Stone>& stones);
};

void Stone::blink(std::vector<Stone>& stones) {
	if (value == 0) value = 1;
	else {
		std::string valueStr = std::to_string(value);
		if (valueStr.size() % 2 == 0) {
			value = std::stoll(valueStr.substr(0, valueStr.size() / 2));
			stones.push_back({ std::stoll(valueStr.substr(valueStr.size() / 2)) });
		}
		else value = value * 2024;
	}
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
	std::vector<Stone> stones;
	for (int i = 0; i < input[0].size(); i++) {
		stones.push_back({ std::stoll(input[0][i]) });
	}

	for (int i = 0; i < 25; i++) {
		for (int j = stones.size() - 1; j >= 0; j--) {
			stones[j].blink(stones);
		}
	}

	std::cout << "Part 1: " << stones.size() << "\n";
	Utils::copy(stones.size());

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