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

enum class Direction { RIGHT = '>', DOWN = 'v', LEFT = '<', UP = '^' };

Utils::Vector2ll pushObject(Direction direction, Utils::Vector2ll position, std::vector<std::string>& map) {
	Utils::Vector2ll target = position;
	switch (direction) {
	case Direction::RIGHT:
		target.x++;
		break;
	case Direction::DOWN:
		target.y++;
		break;
	case Direction::LEFT:
		target.x--;
		break;
	case Direction::UP:
		target.y--;
		break;
	}

	if (map[target.y][target.x] == '.') {
		map[target.y][target.x] = map[position.y][position.x];
		map[position.y][position.x] = '.';
		return target;
	}
	if (map[target.y][target.x] == 'O') {
		if (pushObject(direction, target, map) != target) {
			map[target.y][target.x] = map[position.y][position.x];
			map[position.y][position.x] = '.';
			return target;
		}
		return position;
	}
	return position;
}

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	std::vector<std::string> blocks = Utils::split(rawInput, "\n\n");
	std::vector<std::string> map = Utils::split(blocks[0], "\n");

	// Part 1
	Utils::Vector2ll robot;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == '@') {
				robot = { x, y };
				x = map[y].size() - 1;
				y = map.size() - 1;
			}
		}
	}

	for (int i = 0; i < blocks[1].size(); i++) {
		robot = pushObject(static_cast<Direction>(blocks[1][i]), robot, map);
	}

	long long total = 0;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 'O') {
				total += x + 100 * y;
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