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

struct Sequence {
	long long first, second, third, fourth;

	bool operator<(const Sequence& other) const {
		if (first != other.first) return first < other.first;
		if (second != other.second) return second < other.second;
		if (third != other.third) return third < other.third;
		return fourth < other.fourth;
	}
};

struct SequenceHash {
	size_t operator()(const Sequence& seq) {
		return seq.first ^ seq.second << 1 ^ seq.third << 2 ^ seq.fourth << 3;
	}
};

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
	std::set<Sequence> allSequences;
	std::vector<std::map<Sequence, int>> options;
	for (int i = 0; i < lines.size(); i++) {
		long long secret = std::stoll(lines[i]);
		std::vector<int> prices = { static_cast<int>(secret % 10) };
		std::vector<int> differences;
		options.push_back(std::map<Sequence, int>());
		for (int j = 0; j < 2000; j++) {
			secret = advanceSecret(secret);
			prices.push_back(secret % 10);
			differences.push_back(prices[prices.size() - 1] - prices[prices.size() - 2]);
			if (differences.size() >= 4) {
				Sequence sequence = { differences[differences.size() - 4], differences[differences.size() - 3], differences[differences.size() - 2], differences[differences.size() - 1] };
				allSequences.insert(sequence);
				if (!options[i].count(sequence)) {
					options[i][sequence] = prices[prices.size() - 1];
				}
			}
		}
	}

	long long best = 0;
	Sequence bestSequence = { 0, 0, 0, 0 };
	for (const Sequence& sequence : allSequences) {
		long long total = 0;
		for (int i = 0; i < lines.size(); i++) {
			if (options[i].count(sequence)) total += options[i][sequence];
		}
		if (total > best) {
			best = total;
			bestSequence = sequence;
		}
	}

	std::cout << "Part 2: " << best << "\n";
	Utils::copy(best);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}