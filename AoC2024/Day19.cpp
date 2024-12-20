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

long long matchDesign(std::string design, std::vector<std::string>& towels, std::unordered_map<std::string, long long>& cache) {
	if (cache.count(design)) {
		return cache[design];
	}

	long long total = 0;
	for (int i = 0; i < towels.size(); i++) {
		if (design.substr(0, towels[i].size()) == towels[i]) {
			if (design.size() > towels[i].size()) {
				total += matchDesign(design.substr(towels[i].size()), towels, cache);
			}
			else total++;
		}
	}
	cache[design] = total;
	return total;
}

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	std::vector<std::string> blocks = Utils::split(rawInput, "\n\n");
	std::vector<std::string> towels = Utils::split(blocks[0], ", ");
	std::vector<std::string> designs = Utils::split(blocks[1], "\n");

	// Part 1
	int possible = 0;
	std::unordered_map<std::string, long long> cache;
	for (int i = 0; i < designs.size(); i++) {
		if (matchDesign(designs[i], towels, cache)) {
			possible++;
		}
	}

	std::cout << "Part 1: " << possible << "\n";
	Utils::copy(possible);

	// Part 2
	long long combinations = 0;
	for (int i = 0; i < designs.size(); i++) {
		combinations += matchDesign(designs[i], towels, cache);
	}

	std::cout << "Part 2: " << combinations << "\n";
	Utils::copy(combinations);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}