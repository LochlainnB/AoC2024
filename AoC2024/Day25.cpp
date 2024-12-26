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

struct LockOrKey {
	int a, b, c, d, e;

	bool overlaps(LockOrKey& other) {
		return a + other.a >= 6
			|| b + other.b >= 6
			|| c + other.c >= 6
			|| d + other.d >= 6
			|| e + other.e >= 6;
	}
};

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	// Use lines for 1D vector
	std::vector<std::string> lines = Utils::split(rawInput, "\n\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> input;
	for (int i = 0; i < lines.size(); i++) {
		input.push_back(Utils::split(lines[i], "\n"));
	}

	// Part 1
	std::vector<LockOrKey> locks;
	std::vector<LockOrKey> keys;
	for (int i = 0; i < input.size(); i++) {
		std::vector<LockOrKey>& type = input[i][0] == "#####" ? locks : keys;
		std::vector<int> heights;
		for (int j = 0; j < input[i][0].size(); j++) {
			int height = -1;
			for (int k = 0; k < input[i].size(); k++) {
				if (input[i][k][j] == '#') height++;
			}
			heights.push_back(height);
		}
		type.push_back({ heights[0], heights[1], heights[2], heights[3], heights[4] });
	}

	long long total = 0;
	for (LockOrKey lock : locks) {
		for (LockOrKey key : keys) {
			if (!lock.overlaps(key)) total++;
		}
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

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