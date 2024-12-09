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
	std::vector<File> p2Files = files;
	std::vector<Space> p2Spaces = spaces;

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
	newFiles.clear();
	for (int i = p2Files.size() - 1; i >= 0; i--) {
		bool moved = false;
		for (int j = 0; j < p2Spaces.size(); j++) {
			if (p2Spaces[j].length >= p2Files[i].length) {
				File& file = p2Files[i];
				Space& space = p2Spaces[j];
				if (space.position < file.position) {
					Space newSpace = { file.position, file.length };
					file.position = space.position;
					newFiles.push_back(file);
					spaces.push_back(newSpace);
					moved = true;
					if (p2Spaces[j].length == p2Files[i].length) {
						p2Spaces.erase(p2Spaces.begin() + j);
					}
					else {
						space.length -= file.length;
						space.position += file.length;
					}
				}
				j = p2Spaces.size();
			}
		}
		if (!moved) {
			newFiles.push_back(p2Files[i]);
		}
	}

	checksum = 0;
	for (int i = 0; i < newFiles.size(); i++) {
		checksum += newFiles[i].checksum();
	}

	std::cout << "Part 2: " << checksum << "\n";
	Utils::copy(checksum);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}