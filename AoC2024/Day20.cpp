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

void resetGraph(std::vector<std::vector<Node*>>& graph) {
	for (int y = 0; y < graph.size(); y++) {
		for (int x = 0; x < graph[y].size(); x++) {
			if (graph[y][x]) {
				graph[y][x]->cost = LLONG_MAX;
			}
		}
	}
}

long long aStar(std::vector<std::vector<Node*>>& graph, const Utils::Vector2ll& startPos, const Utils::Vector2ll& endPos) {
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
		input.push_back(Utils::split(lines[i], " "));
	}

	// Part 1
	Utils::Vector2ll startPos;
	Utils::Vector2ll endPos;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			if (lines[y][x] == 'S') {
				startPos = { x, y };
			}
			else if (lines[y][x] == 'E') {
				endPos = { x, y };
			}
		}
	}

	std::vector<std::vector<Node*>> graph(lines.size(), std::vector<Node*>(lines[0].size(), nullptr));
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			if (lines[y][x] != '#') {
				Utils::Vector2ll position = { x, y };
				graph[y][x] = new Node{ position, LLONG_MAX, (endPos - position).getManhattan() };
			}
		}
	}

	long long normalCost = aStar(graph, startPos, endPos);

	int validCheats = 0;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			if (lines[y][x] == '#') {
				resetGraph(graph);
				Utils::Vector2ll position = { x, y };
				graph[y][x] = new Node{ position, LLONG_MAX, (endPos - position).getManhattan() };
				if (aStar(graph, startPos, endPos) <= normalCost - 100) {
					validCheats++;
				}
				delete graph[y][x];
				graph[y][x] = nullptr;
			}
		}
	}

	std::cout << "Part 1: " << validCheats << "\n";
	Utils::copy(validCheats);

	// Part 2
	aStar(graph, startPos, endPos);
	validCheats = 0;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			if (lines[y][x] != '#') {
				long long toCheatCost = graph[y][x]->cost;
				for (int yOff = -20; yOff <= 20; yOff++) {
					for (int xOff = -20 + abs(yOff); xOff <= 20 - abs(yOff); xOff++) {
						Utils::Vector2ll cheatedPos = { x + xOff, y + yOff };
						if (cheatedPos.x >= 0 && cheatedPos.y >= 0 && cheatedPos.x < graph[0].size() && cheatedPos.y < graph.size() && lines[cheatedPos.y][cheatedPos.x] != '#') {
							long long cheatCost = abs(xOff) + abs(yOff);
							long long toEndCost = graph[endPos.y][endPos.x]->cost - graph[cheatedPos.y][cheatedPos.x]->cost;
							long long totalCost = toCheatCost + cheatCost + toEndCost;
							if (totalCost <= normalCost - 100) {
								validCheats++;
							}
						}
					}
				}
			}
		}
	}

	std::cout << "Part 2: " << validCheats << "\n";
	Utils::copy(validCheats);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}