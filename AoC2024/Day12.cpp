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

struct Edge;
struct Plot;
struct Region;

struct pairHash {
	size_t operator()(const std::pair<int, int>& key) const {
		return static_cast<long long>(key.first) << 32 & key.second;
	}
};

struct Edge {
	int length;
};

struct Plot {
	Region* region;
	Edge* upEdge;
	Edge* downEdge;
	Edge* leftEdge;
	Edge* rightEdge;
};

struct Region {
	std::vector<Plot*> plots;
	int fences;
	std::set<Edge*> edges;
};

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	// Use lines for 1D vector
	std::vector<std::string> lines = Utils::split(rawInput, "\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> input;
	for (int i = 0; i < lines.size(); i++) {
		input.push_back(Utils::split(lines[i], " "));
	}

	// Both parts
	std::set<Region*> regions;
	std::unordered_map<std::pair<int, int>, Plot*, pairHash> plotAtPosition;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			Plot* plot = new Plot();
			// Find fences
			std::vector<std::pair<int, int>> neighbors(4, {x, y});
			neighbors[0].first++;
			neighbors[1].first--;
			neighbors[2].second++;
			neighbors[3].second--;
			if (neighbors[0].first >= lines[y].size() || lines[y][x] != lines[neighbors[0].second][neighbors[0].first]) {
				neighbors[0] = { -1, -1 };
				plot->rightEdge = new Edge { 1 };
			}
			if (neighbors[1].first < 0 || lines[y][x] != lines[neighbors[1].second][neighbors[1].first]) {
				neighbors[1] = { -1, -1 };
				plot->leftEdge = new Edge{ 1 };
			}
			if (neighbors[2].second >= lines.size() || lines[y][x] != lines[neighbors[2].second][neighbors[2].first]) {
				neighbors[2] = { -1, -1 };
				plot->downEdge = new Edge{ 1 };
			}
			if (neighbors[3].second < 0 || lines[y][x] != lines[neighbors[3].second][neighbors[3].first]) {
				neighbors[3] = { -1, -1 };
				plot->upEdge = new Edge{ 1 };
			}
			for (int i = 0; i < neighbors.size(); i++) {
				if (neighbors[i] == std::make_pair(-1, -1)) {
					neighbors.erase(neighbors.begin() + i);
					i--;
				}
			}

			// Identify region
			Region* region = nullptr;
			std::vector<Region*> neighborRegions;
			for (int i = 0; i < neighbors.size(); i++) {
				if (plotAtPosition.count(neighbors[i])) {
					neighborRegions.push_back(plotAtPosition[neighbors[i]]->region);
				}
			}
			// Handle multiple Regions that are actually part of the same region
			for (int j = 1; j < neighborRegions.size(); j++) {
				if (neighborRegions[0] != neighborRegions[j]) {
					neighborRegions[0]->fences += neighborRegions[j]->fences;
					neighborRegions[0]->plots.insert(neighborRegions[0]->plots.end(), neighborRegions[j]->plots.begin(), neighborRegions[j]->plots.end());
					neighborRegions[0]->edges.insert(neighborRegions[j]->edges.begin(), neighborRegions[j]->edges.end());
					for (auto record : plotAtPosition) {
						if (record.second->region == neighborRegions[j]) {
							plotAtPosition[record.first]->region = neighborRegions[0];
						}
					}
					regions.erase(neighborRegions[j]);
					delete neighborRegions[j];
				}
			}
			if (neighborRegions.size() > 0) {
				region = neighborRegions[0];
			}
			if (!region) {
				region = new Region();
				regions.insert(region);
			}

			// Part 2
			plot->region = region;
			if (plot->rightEdge != nullptr) {
				if (y > 0 && plotAtPosition[{x, y - 1}]->region == region && plotAtPosition[{x, y - 1}]->rightEdge != nullptr) {
					plotAtPosition[{x, y - 1}]->rightEdge->length++;
					delete plot->rightEdge;
					plot->rightEdge = plotAtPosition[{x, y - 1}]->rightEdge;
				}
				region->edges.insert(plot->rightEdge);
			}
			if (plot->leftEdge != nullptr) {
				if (y > 0 && plotAtPosition[{x, y - 1}]->region == region && plotAtPosition[{x, y - 1}]->leftEdge != nullptr) {
					plotAtPosition[{x, y - 1}]->leftEdge->length++;
					delete plot->leftEdge;
					plot->leftEdge = plotAtPosition[{x, y - 1}]->leftEdge;
				}
				region->edges.insert(plot->leftEdge);
			}
			if (plot->downEdge != nullptr) {
				if (x > 0 && plotAtPosition[{x - 1, y}]->region == region && plotAtPosition[{x - 1, y}]->downEdge != nullptr) {
					plotAtPosition[{x - 1, y}]->downEdge->length++;
					delete plot->downEdge;
					plot->downEdge = plotAtPosition[{x - 1, y}]->downEdge;
				}
				region->edges.insert(plot->downEdge);
			}
			if (plot->upEdge != nullptr) {
				if (x > 0 && plotAtPosition[{x - 1, y}]->region == region && plotAtPosition[{x - 1, y}]->upEdge != nullptr) {
					plotAtPosition[{x - 1, y}]->upEdge->length++;
					delete plot->upEdge;
					plot->upEdge = plotAtPosition[{x - 1, y}]->upEdge;
				}
				region->edges.insert(plot->upEdge);
			}

			// Part 1
			region->plots.push_back(plot);
			region->fences += 4 - neighbors.size();
			plotAtPosition[{x, y}] = plot;
		}
	}

	long long total = 0;
	for (Region* region : regions) {
		total += region->plots.size() * region->fences;
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	total = 0;
	for (Region* region : regions) {
		total += region->edges.size() * region->plots.size();
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