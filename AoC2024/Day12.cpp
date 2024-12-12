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

struct pairHash {
	size_t operator()(const std::pair<int, int>& key) const {
		return static_cast<long long>(key.first) << 32 & key.second;
	}
};

struct Region {
	int plots;
	int fences;
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

	// Part 1
	std::set<Region*> regions;
	std::unordered_map<std::pair<int, int>, Region*, pairHash> regionAtPosition;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			std::vector<std::pair<int, int>> neighbors(4, {x, y});
			neighbors[0].first++;
			neighbors[1].first--;
			neighbors[2].second++;
			neighbors[3].second--;
			for (int i = 0; i < neighbors.size(); i++) {
				if (neighbors[i].first < 0
				|| neighbors[i].second < 0
				|| neighbors[i].first >= lines[y].size()
				|| neighbors[i].second >= lines.size()
				|| lines[y][x] != lines[neighbors[i].second][neighbors[i].first]) {
					neighbors.erase(neighbors.begin() + i);
					i--;
				}
			}
			Region* region = nullptr;
			std::vector<Region*> neighborRegions;
			for (int i = 0; i < neighbors.size(); i++) {
				if (regionAtPosition.count(neighbors[i])) {
					neighborRegions.push_back(regionAtPosition[neighbors[i]]);
				}
			}
			// Handle multiple Regions that are actually part of the same region
			for (int j = 1; j < neighborRegions.size(); j++) {
				if (neighborRegions[0] != neighborRegions[j]) {
					neighborRegions[0]->fences += neighborRegions[j]->fences;
					neighborRegions[0]->plots += neighborRegions[j]->plots;
					for (auto record : regionAtPosition) {
						if (record.second == neighborRegions[j]) {
							regionAtPosition[record.first] = neighborRegions[0];
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
			region->plots++;
			region->fences += 4 - neighbors.size();
			regionAtPosition[{x, y}] = region;
		}
	}

	long long total = 0;
	for (auto region : regions) {
		total += region->plots * region->fences;
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