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

struct Node {
	Utils::Vector2ll position;
	long long cost;
	long long h;
};

struct Comp {
	bool operator()(Node* lhs, Node* rhs) {
		return lhs->cost + lhs->h > rhs->cost + rhs->h;
	}
};

long long aStar(std::vector<std::vector<Node*>>& graph) {
	Utils::Vector2ll startPos = { 0, 0 };
	Utils::Vector2ll endPos = Utils::Vector2ll(graph[0].size() - 1, graph.size() - 1);

	std::priority_queue<Node*, std::vector<Node*>, Comp> openSet;
	Node* start = graph[startPos.y][startPos.x];
	start->cost = 0;
	openSet.push(start);

	long long result = -1;

	while (!openSet.empty()) {
		Node* node = openSet.top();
		openSet.pop();
		std::vector<Node*> candidates;

		if (node->position.x > 0) {
			candidates.push_back(graph[node->position.y][node->position.x - 1]);
		}
		if (node->position.x < graph[0].size() - 1) {
			candidates.push_back(graph[node->position.y][node->position.x + 1]);
		}
		if (node->position.y > 0) {
			candidates.push_back(graph[node->position.y - 1][node->position.x]);
		}
		if (node->position.y < graph.size() - 1) {
			candidates.push_back(graph[node->position.y + 1][node->position.x]);
		}

		for (int i = 0; i < candidates.size(); i++) {
			if (candidates[i] != nullptr && candidates[i]->cost > node->cost + 1) {
				candidates[i]->cost = node->cost + 1;
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
		input.push_back(Utils::split(lines[i], ","));
	}

	// Part 1
	std::set<Utils::Vector2ll> corruption;
	for (int i = 0; i < (file == "Test.txt" ? 12 : 1024); i++) {
		corruption.insert({ std::stoi(input[i][0]), std::stoi(input[i][1]) });
	}

	int size = file == "Test.txt" ? 7 : 71;
	Utils::Vector2ll endPos = { size - 1, size - 1 };
	std::vector<std::vector<Node*>> graph(size, std::vector<Node*>(size, nullptr));
	for (int y = 0; y < graph.size(); y++) {
		for (int x = 0; x < graph[0].size(); x++) {
			if (corruption.count({ x, y }) == 0) {
				graph[y][x] = new Node{ {x, y}, LLONG_MAX, (endPos - Utils::Vector2ll(x, y)).getManhattan() };
			}
		}
	}

	long long steps = aStar(graph);

	std::cout << "Part 1: " << steps << "\n";
	Utils::copy(steps);

	// Part 2
	int byte = 0;
	while (steps != -1) {
		byte++;
		for (int y = 0; y < graph.size(); y++) {
			for (int x = 0; x < graph[0].size(); x++) {
				if (graph[y][x] != nullptr) {
					graph[y][x]->cost = LLONG_MAX;
				}
			}
		}
		Node* node = graph[std::stoi(input[byte][1])][std::stoi(input[byte][0])];
		if (node) delete node;
		graph[std::stoi(input[byte][1])][std::stoi(input[byte][0])] = nullptr;
		steps = aStar(graph);
	}

	std::cout << "Part 2: " << input[byte][0] << "," << input[byte][1] << "\n";
	Utils::copy(input[byte][0] + "," + input[byte][1]);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}