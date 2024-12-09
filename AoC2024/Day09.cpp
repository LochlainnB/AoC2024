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

struct File {
	long long position;
	long long length;
	long long id;

	long long checksum() {
		return position * id * length + (static_cast<double>((length - 1) * (length - 1)) / 2 + static_cast<double>(length - 1) / 2) * id;
	}
};

struct Space {
	long long position;
	long long length;
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
	long long position = 0;
	bool isFile = true;
	std::vector<File> files;
	std::vector<Space> spaces;
	for (int i = 0; i < rawInput.size(); i++) {
		long long length = std::stoi(std::string(1, rawInput[i]));
		if (isFile) {
			files.push_back({ position, length, static_cast<long long>(files.size()) });
		}
		else {
			spaces.push_back({ position, length });
		}
		position += length;
		isFile = !isFile;
	}

	std::vector<File> newFiles;
	isFile = true;
	while (files.size() > 0) {
		if (isFile) {
			newFiles.push_back(files[0]);
			files.erase(files.begin());
			isFile = false;
		}
		else {
			Space& space = spaces[0];
			File& file = files[files.size() - 1];
			if (space.length == file.length) {
				file.position = space.position;
				newFiles.push_back(file);
				files.erase(files.begin() + files.size() - 1);
				spaces.erase(spaces.begin());
				isFile = true;
			}
			else if (space.length > file.length) {
				file.position = space.position;
				newFiles.push_back(file);
				space.position += file.length;
				space.length -= file.length;
				files.erase(files.begin() + files.size() - 1);
			}
			else {
				File splitFile = file;
				splitFile.position = space.position;
				splitFile.length = space.length;
				newFiles.push_back(splitFile);
				file.length -= space.length;
				spaces.erase(spaces.begin());
				isFile = true;
			}
		}
	}

	long long checksum = 0;
	for (int i = 0; i < newFiles.size(); i++) {
		checksum += newFiles[i].checksum();
	}

	std::cout << "Part 1: " << checksum << "\n";
	Utils::copy(checksum);

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