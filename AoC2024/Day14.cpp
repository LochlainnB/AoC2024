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

struct Robot {
	Utils::Vector2ll position;
	Utils::Vector2ll velocity;
	Utils::Vector2ll boardSize;
	void update();
};

void Robot::update() {
	position += velocity;
	if (position.x < 0) position.x += boardSize.x;
	else if (position.x >= boardSize.x) position.x -= boardSize.x;
	if (position.y < 0) position.y += boardSize.y;
	else if (position.y >= boardSize.y) position.y -= boardSize.y;
}

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	// Use lines for 1D vector
	std::vector<std::string> lines = Utils::split(rawInput, "\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> pv;
	for (int i = 0; i < lines.size(); i++) {
		pv.push_back(Utils::split(lines[i], " "));
	}
	std::vector<std::vector<std::vector<std::string>>> input;
	for (int i = 0; i < pv.size(); i++) {
		input.push_back(std::vector<std::vector<std::string>>());
		for (int j = 0; j < pv[i].size(); j++) {
			input[i].push_back(Utils::split(pv[i][j], ","));
		}
	}

	// Part 1
	std::vector<int> quadrants = { 0, 0, 0, 0 };
	Utils::Vector2ll boardSize;
	if (file == "Test.txt") {
		boardSize = { 11, 7 };
	}
	else {
		boardSize = { 101, 103 };
	}
	Utils::Vector2ll middle = { (boardSize.x - 1) / 2, (boardSize.y - 1) / 2 };

	for (int i = 0; i < input.size(); i++) {
		Robot robot = { Utils::Vector2ll(std::stoll(input[i][0][0]), std::stoll(input[i][0][1])), Utils::Vector2ll(std::stoll(input[i][1][0]), std::stoll(input[i][1][1])), boardSize };
		for (int j = 0; j < 100; j++) {
			robot.update();
		}
		
		if (robot.position.x < middle.x) {
			if (robot.position.y < middle.y) {
				quadrants[0]++;
			}
			else if (robot.position.y > middle.y) {
				quadrants[1]++;
			}
		}
		else if (robot.position.x > middle.x) {
			if (robot.position.y < middle.y) {
				quadrants[2]++;
			}
			else if (robot.position.y > middle.y) {
				quadrants[3]++;
			}
		}
	}

	long long safetyFactor = 1;
	for (int i = 0; i < quadrants.size(); i++) {
		safetyFactor *= quadrants[i];
	}

	std::cout << "Part 1: " << safetyFactor << "\n";
	Utils::copy(safetyFactor);

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