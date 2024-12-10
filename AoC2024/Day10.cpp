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

struct Candidate {
	Candidate(std::pair<int, int> position, char requiredHeight) {
		this->position = position;
		this->requiredHeight = requiredHeight;
	}

	bool operator<(const Candidate& other) const {
		if (position.first != other.position.first) {
			return position.first < other.position.first;
		}
		else if (position.second != other.position.second) {
			return position.second < other.position.second;
		}
		else {
			return requiredHeight < other.requiredHeight;
		}
	}

	std::pair<int, int> position;
	char requiredHeight;
};

int getScore(std::pair<int, int> start, std::vector<std::string>& map) {
	int score = 0;
	std::queue<Candidate> openSet;
	std::set<Candidate> closedSet;
	openSet.push({ start, '1' });

	while (!openSet.empty()) {
		Candidate& candidate = openSet.front();
		int& x = candidate.position.first;
		int& y = candidate.position.second;
		char& height = candidate.requiredHeight;
		std::vector<Candidate> newCandidates;
		if (y > 0 && map[y - 1][x] == height) {
			newCandidates.push_back(Candidate(std::make_pair(x, y - 1), height + 1));
		}
		if (y < map.size() - 1 && map[y + 1][x] == height) {
			newCandidates.push_back(Candidate(std::make_pair(x, y + 1), height + 1));
		}
		if (x > 0 && map[y][x - 1] == height) {
			newCandidates.push_back(Candidate(std::make_pair(x - 1, y), height + 1));
		}
		if (x < map[y].size() - 1 && map[y][x + 1] == height) {
			newCandidates.push_back(Candidate(std::make_pair(x + 1, y), height + 1));
		}
		for (int i = 0; i < newCandidates.size(); i++) {
			if (!closedSet.count(newCandidates[i])) {
				closedSet.insert(newCandidates[i]); // Any route will do
				if (newCandidates[i].requiredHeight > '9') {
					score++;
				}
				else {
					openSet.push(newCandidates[i]);
				}
			}
		}
		openSet.pop();
	}

	return score;
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
	int total = 0;
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 0; j < lines[i].size(); j++) {
			if (lines[i][j] == '0') {
				total += getScore({ j, i }, lines);
			}
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