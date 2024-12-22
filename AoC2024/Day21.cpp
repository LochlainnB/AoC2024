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

std::map<std::string, std::vector<std::string>> codePaths = {
	{"AA", {""}},
	{"A0", {"<"}},
	{"A1", {"^<<"}},
	{"A2", {"^<", "<^"}},
	{"A3", {"^"}},
	{"A4", {"^^<<"}},
	{"A5", {"^^<", "<^^"}},
	{"A6", {"^^"}},
	{"A7", {"^^^<<"}},
	{"A8", {"^^^<", "<^^^"}},
	{"A9", {"^^^"}},

	{"0A", {">"}},
	{"00", {""}},
	{"01", {"^<"}},
	{"02", {"^"}},
	{"03", {"^>", ">^"}},
	{"04", {"^^<"}},
	{"05", {"^^"}},
	{"06", {"^^>", ">^^"}},
	{"07", {"^^^<"}},
	{"08", {"^^^"}},
	{"09", {"^^^>", ">^^^"}},

	{"1A", {">>v"}},
	{"10", {">v"}},
	{"11", {""}},
	{"12", {">"}},
	{"13", {">>"}},
	{"14", {"^"}},
	{"15", {"^>", ">^"}},
	{"16", {"^>>", ">>^"}},
	{"17", {"^^"}},
	{"18", {"^^>", ">^^"}},
	{"19", {"^^>>", ">>^^"}},

	{"2A", {"v>", ">v"}},
	{"20", {"v"}},
	{"21", {"<"}},
	{"22", {""}},
	{"23", {">"}},
	{"24", {"^<", "<^"}},
	{"25", {"^"}},
	{"26", {"^>", ">^"}},
	{"27", {"^^<", "<^^"}},
	{"28", {"^"}},
	{"29", {"^^>", ">^^"}},

	{"3A", {"v"}},
	{"30", {"v<", "<v"}},
	{"31", {"<<"}},
	{"32", {"<"}},
	{"33", {""}},
	{"34", {"^<<", "<<^"}},
	{"35", {"^<", "<^"}},
	{"36", {"^"}},
	{"37", {"^^<<", "<<^^"}},
	{"38", {"^^<", "<^^"}},
	{"39", {"^^"}},

	{"4A", {">>vv"}},
	{"40", {">vv"}},
	{"41", {"v"}},
	{"42", {"v>", ">v"}},
	{"43", {"v>>", ">>v"}},
	{"44", {""}},
	{"45", {">"}},
	{"46", {">>"}},
	{"47", {"^"}},
	{"48", {"^>", ">^"}},
	{"49", {"^>>", ">>^"}},

	{"5A", {"vv>", ">vv"}},
	{"50", {"vv"}},
	{"51", {"v<", "<v"}},
	{"52", {"v"}},
	{"53", {"v>", ">v"}},
	{"54", {"<"}},
	{"55", {""}},
	{"56", {">"}},
	{"57", {"^<", "<^"}},
	{"58", {"^"}},
	{"59", {"^>", ">^"}},

	{"6A", {"vv"}},
	{"60", {"vv<", "<vv"}},
	{"61", {"v<<", "<<v"}},
	{"62", {"v<", "<v"}},
	{"63", {"v"}},
	{"64", {"<<"}},
	{"65", {"<"}},
	{"66", {""}},
	{"67", {"^<<", "<<^"}},
	{"68", {"^<", "<^"}},
	{"69", {"^"}},

	{"7A", {">>vvv"}},
	{"70", {">vvv"}},
	{"71", {"vv"}},
	{"72", {"vv>", ">vv"}},
	{"73", {"vv>>", ">>vv"}},
	{"74", {"v"}},
	{"75", {"v>", ">v"}},
	{"76", {"v>>", ">>v"}},
	{"77", {""}},
	{"78", {">"}},
	{"79", {">>"}},

	{"8A", {"vvv>", ">vvv"}},
	{"80", {"vvv"}},
	{"81", {"vv<", "<vv"}},
	{"82", {"vv"}},
	{"83", {"vv>", ">vv"}},
	{"84", {"v<", "<v"}},
	{"85", {"v"}},
	{"86", {"v>", ">v"}},
	{"87", {"<"}},
	{"88", {""}},
	{"89", {">"}},

	{"9A", {"vvv"}},
	{"90", {"vvv<", "<vvv"}},
	{"91", {"vv<<", "<<vv"}},
	{"92", {"vv<", "<vv"}},
	{"93", {"vv"}},
	{"94", {"v<<", "<<v"}},
	{"95", {"v<", "<v"}},
	{"96", {"v"}},
	{"97", {"<<"}},
	{"98", {"<"}},
	{"99", {""}}
};

std::vector<std::string> codeToDirectional(std::string code) {
	code = "A" + code;
	std::vector<std::string> results = {""};
	for (int i = 0; i < code.size() - 1; i++) {
		std::vector<std::string> newResults;
		std::string key = code.substr(i, 2);
		for (int j = 0; j < results.size(); j++) {
			for (int k = 0; k < codePaths[key].size(); k++) {
				newResults.push_back(results[j] + codePaths[key][k] + "A");
			}
		}
		results = newResults;
	}
	return results;
}

std::map<std::string, std::vector<std::string>> directionalPaths = {
	{"AA", {""}},
	{"A^", {"<"}},
	{"A>", {"v"}},
	{"Av", {"v<", "<v"}},
	{"A<", {"v<<"}},

	{"^A", {">"}},
	{"^^", {""}},
	{"^>", {"v>", ">v"}},
	{"^v", {"v"}},
	{"^<", {"v<"}},

	{">A", {"^"}},
	{">^", {"^<", "<^"}},
	{">>", {""}},
	{">v", {"<"}},
	{"><", {"<"}},

	{"vA", {"^>", ">^"}},
	{"v^", {"^"}},
	{"v>", {">"}},
	{"vv", {""}},
	{"v<", {"<"}},

	{"<A", {">>^"}},
	{"<^", {">^"}},
	{"<>", {">>"}},
	{"<v", {">"}},
	{"<<", {""}},
};

struct cacheHash {
	size_t operator()(const std::pair<std::string, int>& key) const {
		return std::hash<std::string>()(key.first) ^ (std::hash<int>()(key.second) << 1);
	}
};

long long directionalToDirectional(std::string input, int levels, std::unordered_map<std::pair<std::string, int>, long long, cacheHash>& cache) {
	input = "A" + input;

	std::pair<std::string, int> key = { input, levels };
	if (cache.count(key)) {
		return cache[key];
	}
	
	long long result = 0;
	for (int i = 0; i < input.size() - 1; i++) {
		std::string key = input.substr(i, 2);
		long long newResult = LLONG_MAX;
		for (int j = 0; j < directionalPaths[key].size(); j++) {
			std::string part = directionalPaths[key][j] + "A";
			if (levels > 1) {
				newResult = min(newResult, directionalToDirectional(part, levels - 1, cache));
			}
			else {
				newResult = min(newResult, part.size());
			}
		}
		if (newResult != LLONG_MAX) {
			result += newResult;
		}
	}
	cache[{ input, levels }] = result;
	return result;
}

std::vector<long long> directionalToDirectional(std::vector<std::string> input, int levels, std::unordered_map<std::pair<std::string, int>, long long, cacheHash>& cache) {
	std::vector<long long> results;
	for (int i = 0; i < input.size(); i++) {
		results.push_back(directionalToDirectional(input[i], levels, cache));
	}
	return results;
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
	long long total = 0;
	std::unordered_map<std::pair<std::string, int>, long long, cacheHash> cache;
	for (int i = 0; i < lines.size(); i++) {
		long long codeNumeric = std::stoll(lines[i].substr(0, lines[i].size() - 1));
		std::vector<std::string> firstLevel = codeToDirectional(lines[i]);
		std::vector<long long> finalLengths = directionalToDirectional(firstLevel, 2, cache);
		size_t lowest = MAXSIZE_T;
		for (int j = 0; j < finalLengths.size(); j++) {
			if (finalLengths[j] < lowest) {
				lowest = finalLengths[j];
			}
		}
		total += codeNumeric * lowest;
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2
	total = 0;
	for (int i = 0; i < lines.size(); i++) {
		long long codeNumeric = std::stoll(lines[i].substr(0, lines[i].size() - 1));
		std::vector<std::string> firstLevel = codeToDirectional(lines[i]);
		std::vector<long long> finalLengths = directionalToDirectional(firstLevel, 25, cache);
		long long lowest = LLONG_MAX;
		for (int j = 0; j < finalLengths.size(); j++) {
			if (finalLengths[j] < lowest) {
				lowest = finalLengths[j];
			}
		}
		total += codeNumeric * lowest;
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