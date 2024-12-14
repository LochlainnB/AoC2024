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
	std::vector<std::string> machines = Utils::split(rawInput, "\n\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> lines;
	for (int i = 0; i < machines.size(); i++) {
		lines.push_back(Utils::split(machines[i], "\n"));
	}
	std::vector<std::vector<std::vector<std::string>>> input;
	for (int i = 0; i < lines.size(); i++) {
		input.push_back({});
		for (int j = 0; j < lines[i].size(); j++) {
			input[i].push_back(Utils::split(lines[i][j], " "));
		}
	}

	// Part 1
	long long total = 0;
	for (int i = 0; i < input.size(); i++) {
		int x = 0;
		int y = 0;
		int aX = std::stoi(input[i][0][0]);
		int aY = std::stoi(input[i][0][1]);
		int bX = std::stoi(input[i][1][0]);
		int bY = std::stoi(input[i][1][1]);
		int pX = std::stoi(input[i][2][0]);
		int pY = std::stoi(input[i][2][1]);
		int cost = INT_MAX;

		if (pX % bX == 0 && pY % bY == 0 && pX / bX == pY / bY) {
			if (pX / bX <= 100)
				cost = pX / bX;
		}
		if (pX % aX == 0 && pY % aY == 0 && pX / aX == pY / aY) {
			if (pX / aX <= 100)
				cost = min(3 * pX / aX, cost);
		}
		int presses = 0;
		while (presses < 100) {
			presses++;

			x += bX;
			y += bY;
			int rX = pX - x;
			int rY = pY - y;
			if (rX % aX == 0 && rY % aY == 0 && rX / aX == rY / aY) {
				int aPresses = rX / aX;
				if (aPresses <= 100) {
					cost = min(presses + 3 * aPresses, cost);
				}
			}
		}

		x = 0;
		y = 0;
		presses = 0;
		while (presses < 100) {
			presses++;

			x += aX;
			y += aY;
			int rX = pX - x;
			int rY = pY - y;
			if (rX % bX == 0 && rY % bY == 0 && rX / bX == rY / bY) {
				int bPresses = rX / bX;
				if (bPresses <= 100) {
					cost = min(presses * 3 + bPresses, cost);
				}
			}
		}
		if (cost < INT_MAX) {
			total += cost;
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