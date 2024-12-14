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
#include <thread>
#include <mutex>

void getMachineCosts(std::vector<std::vector<std::vector<std::string>>>& input, long long& output, int& index, std::mutex& globalMutex) {
	globalMutex.lock();
	while (index < input.size()) {
		int i = index;
		index++;
		std::cout << "Started machine #" << i << "\n";
		globalMutex.unlock();

		long long x = 0;
		long long y = 0;
		int aX = std::stoi(input[i][0][0]);
		int aY = std::stoi(input[i][0][1]);
		int bX = std::stoi(input[i][1][0]);
		int bY = std::stoi(input[i][1][1]);
		long long pX = std::stoll(input[i][2][0]) + 10000000000000;
		long long pY = std::stoll(input[i][2][1]) + 10000000000000;

		long long presses = 0;
		bool done = false;
		long long cycleBeginX = -1;
		std::set<int> remaindersX;
		while (!done) {
			long long rX = pX - x;
			if (rX % aX == 0) {
				if (cycleBeginX == -1) {
					remaindersX.clear();
					cycleBeginX = x;
				}
				else {

					long long cycleXPresses = (x - cycleBeginX) / bX;
					long long cycleBeginY = -1;
					std::set<int> remaindersY;
					while (!done) {
						long long rY = pY - y;
						if (rY % aY == 0) {
							if (cycleBeginY == -1) {
								remaindersY.clear();
								cycleBeginY = y;
							}
							else {

								long long cycleYPresses = (y - cycleBeginY) / bY;
								while (!done) {
									rX = pX - x;
									rY = pY - y;
									if (rX / aX == rY / aY) {
										globalMutex.lock();
										output += presses + 3 * rX / aX;
										globalMutex.unlock();
										done = true;
									}

									if (!done) {
										x += cycleYPresses * bX;
										y += cycleYPresses * bY;
										presses += cycleYPresses;

										if (x > pX || y > pY) {
											done = true;
										}
									}
								}
							}
						}
						else {
							if (remaindersY.count(rY % aY)) {
								done = true;
							}
							else {
								remaindersY.insert(rY % aY);
							}
						}

						if (!done) {
							x += cycleXPresses * bX;
							y += cycleXPresses * bY;
							presses += cycleXPresses;
						}
					}
				}
			}
			else {
				if (remaindersX.count(rX % aX)) {
					done = true;
				}
				else {
					remaindersX.insert(rX % aX);
				}
			}

			if (!done) {
				x += bX;
				y += bY;
				presses++;
			}
		}
		globalMutex.lock();
		std::cout << "Finished machine #" << i << "\n";
	}
	globalMutex.unlock();
}

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	// Use lines for 1D vector
	std::vector<std::string> machines = Utils::split(rawInput, "\n\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> lines;
	for (int i = 0; i < machines.size(); i++) {
		lines.push_back(Utils::split(machines[i], "\n"));
	}
	std::vector<std::vector<std::vector<std::string>>> input;
	for (int i = 0; i < lines.size(); i++) {
		input.push_back({});
		for (int j = 0; j < lines[i].size(); j++) {
			input[i].push_back(Utils::split(lines[i][j], " "));
		}
	}

	// Part 1 - Covering every edge case, even those that don't exist!
	long long total = 0;
	for (int i = 0; i < input.size(); i++) {
		int x = 0;
		int y = 0;
		int aX = std::stoi(input[i][0][0]);
		int aY = std::stoi(input[i][0][1]);
		int bX = std::stoi(input[i][1][0]);
		int bY = std::stoi(input[i][1][1]);
		int pX = std::stoi(input[i][2][0]);
		int pY = std::stoi(input[i][2][1]);
		int cost = INT_MAX;

		if (pX % bX == 0 && pY % bY == 0 && pX / bX == pY / bY) {
			if (pX / bX <= 100)
				cost = pX / bX;
		}
		if (pX % aX == 0 && pY % aY == 0 && pX / aX == pY / aY) {
			if (pX / aX <= 100)
				cost = min(3 * pX / aX, cost);
		}
		int presses = 0;
		while (presses < 100) {
			presses++;

			x += bX;
			y += bY;
			int rX = pX - x;
			int rY = pY - y;
			if (rX % aX == 0 && rY % aY == 0 && rX / aX == rY / aY) {
				int aPresses = rX / aX;
				if (aPresses <= 100) {
					cost = min(presses + 3 * aPresses, cost);
				}
			}
		}

		x = 0;
		y = 0;
		presses = 0;
		while (presses < 100) {
			presses++;

			x += aX;
			y += aY;
			int rX = pX - x;
			int rY = pY - y;
			if (rX % bX == 0 && rY % bY == 0 && rX / bX == rY / bY) {
				int bPresses = rX / bX;
				if (bPresses <= 100) {
					cost = min(presses * 3 + bPresses, cost);
				}
			}
		}
		if (cost < INT_MAX) {
			total += cost;
		}
	}

	std::cout << "Part 1: " << total << "\n";
	Utils::copy(total);

	// Part 2
	total = 0;
	int numThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(numThreads);
	int index = 0;
	std::mutex globalMutex;
	for (int i = 0; i < numThreads; i++) {
		threads[i] = std::thread(getMachineCosts, std::ref(input), std::ref(total), std::ref(index), std::ref(globalMutex));
	}
	for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
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