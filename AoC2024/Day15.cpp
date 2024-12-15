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

bool pushWideBox(Direction direction, Utils::Vector2ll position, std::vector<std::string>& map) {
	std::vector<Utils::Vector2ll> parts(1, position);
	if (direction == Direction::DOWN || direction == Direction::UP) {
		parts.push_back(position);
		if (map[position.y][position.x] == '[') {
			parts[1].x++;
		}
		else {
			parts[1].x--;
		}
	}

	bool partsMoved = true;
	std::vector<Utils::Vector2ll> targets;
	for (int i = 0; i < parts.size(); i++) {
		targets.push_back(parts[i]);
		Utils::Vector2ll& target = targets[targets.size() - 1];
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

		if (map[target.y][target.x] == '#') {
			partsMoved = false;
			break;
		}
		else if (map[target.y][target.x] == '[') {
			parts.push_back(target);
			if (direction == Direction::DOWN || direction == Direction::UP) {
				parts.push_back({ target.x + 1, target.y });
			}
		}
		else if (map[target.y][target.x] == ']') {
			parts.push_back(target);
			if (direction == Direction::DOWN || direction == Direction::UP) {
				parts.push_back({ target.x - 1, target.y });
			}
		}
	}

	std::set<Utils::Vector2ll> processed;
	if (partsMoved) {
		for (int i = parts.size() - 1; i >= 0; i--) {
			if (processed.count(parts[i])) continue;
			processed.insert(parts[i]);
			map[targets[i].y][targets[i].x] = map[parts[i].y][parts[i].x];
			map[parts[i].y][parts[i].x] = '.';
		}
		return true;
	}
	return false;
}

Utils::Vector2ll pushObject(Direction direction, Utils::Vector2ll position, std::vector<std::string>& map, bool part2 = false) {
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
	if (!part2) {
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
	// Part 2
	if (map[target.y][target.x] == '[' || map[target.y][target.x] == ']') {
		if (pushWideBox(direction, target, map)) {
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
	std::vector<std::string> startMap = Utils::split(blocks[0], "\n");

	// Part 1
	Utils::Vector2ll robot;
	std::vector<std::string> map = startMap;
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
	map = startMap;
	std::vector<std::string> bigMap;
	for (int y = 0; y < map.size(); y++) {
		bigMap.push_back("");
		for (int x = 0; x < map[y].size(); x++) {
			switch (map[y][x]) {
			case '#':
				bigMap[y] += "##";
				break;
			case '.':
				bigMap[y] += "..";
				break;
			case 'O':
				bigMap[y] += "[]";
				break;
			case '@':
				bigMap[y] += "@.";
				robot = { x * 2, y };
				break;
			}
		}
	}

	for (int i = 0; i < blocks[1].size(); i++) {
		robot = pushObject(static_cast<Direction>(blocks[1][i]), robot, bigMap, true);
	}

	total = 0;
	for (int y = 0; y < bigMap.size(); y++) {
		for (int x = 0; x < bigMap[y].size(); x++) {
			if (bigMap[y][x] == '[') {
				total += x + 100 * y;
			}
		}
	}

	std::cout << "Part 2: " << total << "\n";
	Utils::copy(total);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}