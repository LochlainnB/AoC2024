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

struct pairHash {
	size_t operator()(const std::pair<long long, int>& key) const {
		return key.first * key.second;
	}
};

long long getStones(long long value, int blinks, std::unordered_map<std::pair<long long, int>, long long, pairHash>& cache) {
	if (blinks == 0) {
		return 1;
	}
	if (cache.count({ value, blinks })) {
		return cache[{value, blinks}];
	}
	
	if (value == 0) cache[{value, blinks}] = getStones(1, blinks - 1, cache);
	else {
		std::string valueStr = std::to_string(value);
		if (valueStr.size() % 2 == 0) cache[{value, blinks}] = getStones(std::stoll(valueStr.substr(0, valueStr.size() / 2)), blinks - 1, cache)
									+ getStones(std::stoll(valueStr.substr(valueStr.size() / 2)), blinks - 1, cache);
		else cache[{value, blinks}] = getStones(value * 2024, blinks - 1, cache);
	}
	return cache[{value, blinks}];
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
	long long stoneCount = 0;
	std::unordered_map<std::pair<long long, int>, long long, pairHash> cache;
	for (int i = 0; i < input[0].size(); i++) {
		stoneCount += getStones(std::stoll(input[0][i]), 75, cache);
	}

	std::cout << "Part 2: " << stoneCount << "\n";
	Utils::copy(stoneCount);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}