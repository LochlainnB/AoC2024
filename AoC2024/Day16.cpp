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

enum class Direction { RIGHT, DOWN, LEFT, UP };

struct Node {
	Utils::Vector2ll position;
	Direction direction;
	long long cost;
	long long h;
};

struct Comp {
	bool operator()(Node* lhs, Node* rhs) {
		return lhs->cost + lhs->h > rhs->cost + rhs->h;
	}
};

long long aStar(std::vector<std::string>& map) {
	Utils::Vector2ll startPos = Utils::Vector2ll(1, map.size() - 2);
	Utils::Vector2ll endPos = Utils::Vector2ll(map[0].size() - 2, 1);

	std::vector<std::vector<std::vector<Node*>>> graph(map.size(), std::vector<std::vector<Node*>>(map[0].size(), std::vector<Node*>(4, nullptr)));
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[0].size(); x++) {
			if (map[y][x] != '#') {
				for (int d = 0; d < 4; d++) {
					graph[y][x][d] = new Node{ {x, y}, static_cast<Direction>(d), LLONG_MAX, (endPos - Utils::Vector2ll(x, y)).getManhattan() };
				}
			}
		}
	}

	std::priority_queue<Node*, std::vector<Node*>, Comp> openSet;
	Node* start = graph[startPos.y][startPos.x][static_cast<int>(Direction::RIGHT)];
	start->cost = 0;
	openSet.push(start);

	while (!openSet.empty()) {
		Node* node = openSet.top();
		openSet.pop();
		std::vector<Node*> candidates;

		switch (node->direction) {
		case Direction::RIGHT:
			candidates.push_back(graph[node->position.y][node->position.x + 1][static_cast<int>(node->direction)]);
			break;
		case Direction::DOWN:
			candidates.push_back(graph[node->position.y + 1][node->position.x][static_cast<int>(node->direction)]);
			break;
		case Direction::LEFT:
			candidates.push_back(graph[node->position.y][node->position.x - 1][static_cast<int>(node->direction)]);
			break;
		case Direction::UP:
			candidates.push_back(graph[node->position.y - 1][node->position.x][static_cast<int>(node->direction)]);
			break;
		}

		candidates.push_back(graph[node->position.y][node->position.x][(static_cast<int>(node->direction) + 1) % 4]);
		candidates.push_back(graph[node->position.y][node->position.x][(static_cast<int>(node->direction) + 3) % 4]);

		for (int i = 0; i < candidates.size(); i++) {
			int addedCost = i > 0 ? 1000 : 1;
			if (candidates[i] != nullptr && candidates[i]->cost > node->cost + addedCost) {
				candidates[i]->cost = node->cost + addedCost;
				openSet.push(candidates[i]);
				if (candidates[i]->position == endPos) {
					return candidates[i]->cost;
				}
			}
		}
	}
	return -1;
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
	long long total = aStar(lines);

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