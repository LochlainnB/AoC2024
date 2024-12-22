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

long long advanceSecret(long long secret) {
	secret = (secret ^ secret * 64) % 16777216;
	secret = (secret / 32 ^ secret) % 16777216;
	secret = (secret ^ secret * 2048) % 16777216;
	return secret;
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
	long long total = 0;
	for (int i = 0; i < lines.size(); i++) {
		long long secret = std::stoll(lines[i]);
		for (int j = 0; j < 2000; j++) {
			secret = advanceSecret(secret);
		}
		total += secret;
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