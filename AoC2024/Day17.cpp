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

class Computer {
public:
	Computer();

	std::string run(const long long& a, const long long& b, const long long& c, const std::vector<std::string>& program, bool verify = false);

private:
	long long getCombo(int operand);

	void adv(int operand);
	void bxl(int operand);
	void bst(int operand);
	void jnz(int operand);
	void bxc(int operand);
	bool out(int operand);
	void bdv(int operand);
	void cdv(int operand);

	long long a, b, c;
	std::vector<int> program;
	int instructionPointer;
	std::vector<int> output;
};

Computer::Computer() {
	a = b = c = 0;
	instructionPointer = 0;
}

std::string Computer::run(const long long& a, const long long& b, const long long& c, const std::vector<std::string>& program, bool verify) {
	this->a = a;
	this->b = b;
	this->c = c;
	instructionPointer = 0;
	output.clear();
	this->program.clear();
	for (int i = 0; i < program.size(); i++) {
		this->program.push_back(std::stoi(program[i]));
	}

	while (instructionPointer < this->program.size()) {
		int opcode = this->program[instructionPointer];
		int operand = this->program[instructionPointer + 1];
		switch (opcode) {
		case 0:
			adv(operand);
			break;
		case 1:
			bxl(operand);
			break;
		case 2:
			bst(operand);
			break;
		case 3:
			jnz(operand);
			break;
		case 4:
			bxc(operand);
			break;
		case 5:
			if (!out(operand) && verify) return "";
			break;
		case 6:
			bdv(operand);
			break;
		case 7:
			cdv(operand);
			break;
		default:
			throw "Invalid opcode";
		}
	}

	std::string outputString;
	for (int i = 0; i < output.size(); i++) {
		outputString += std::to_string(output[i]) + ",";
	}
	if (outputString.size() > 0) {
		outputString.erase(outputString.begin() + outputString.size() - 1);
	}
	return outputString;
}

long long Computer::getCombo(int operand) {
	switch (operand) {
	case 4:
		return a;
	case 5:
		return b;
	case 6:
		return c;
	case 7:
		throw "Invalid combo operand";
	default:
		return operand;
	}

}

void Computer::adv(int operand) {
	a = a >> getCombo(operand);
	instructionPointer += 2;
}

void Computer::bxl(int operand) {
	b = b ^ operand;
	instructionPointer += 2;
}

void Computer::bst(int operand) {
	b = getCombo(operand) & 7;
	instructionPointer += 2;
}

void Computer::jnz(int operand) {
	if (a != 0) {
		instructionPointer = operand;
	}
	else {
		instructionPointer += 2;
	}
}

void Computer::bxc(int operand) {
	b = b ^ c;
	instructionPointer += 2;
}

bool Computer::out(int operand) {
	output.push_back(getCombo(operand) & 7);
	instructionPointer += 2;
	int index = output.size() - 1;
	return index < program.size() && output[index] == program[index];
}

void Computer::bdv(int operand) {
	b = a >> getCombo(operand);
	instructionPointer += 2;
}

void Computer::cdv(int operand) {
	c = a >> getCombo(operand);
	instructionPointer += 2;
}

long long getA(const std::vector<int>& program, long long currentA) {
	int target = program[0];
	std::vector<int> newProgram = program;
	newProgram.erase(newProgram.begin());
	for (int i = 0; i <= 0b111; i++) {
		long long aPart = static_cast<long long>(i) | currentA << 3;
		long long actual = (aPart % 8) ^ 5 ^ (aPart >> ((aPart % 8) ^ 1));

		if ((actual & 0b111) == target) {
			if (newProgram.size() == 0) {
				return aPart;
			}
			long long a = getA(newProgram, aPart);
			if (a != -1) {
				return a;
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
	Computer computer;
	std::string output = computer.run(std::stoll(input[0][0]), std::stoll(input[1][0]), std::stoll(input[2][0]), input[3]);

	std::cout << "Part 1: " << output << "\n";
	Utils::copy(output);

	// Part 2
	std::vector<int> program;
	for (int i = input[3].size() - 1; i >= 0; i--) {
		program.push_back(std::stoi(input[3][i]));
	}
	long long a = getA(program, 0);

	std::cout << "Part 2: " << a << "\n";
	Utils::copy(a);
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}