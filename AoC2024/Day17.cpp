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

	std::string run(const long long& a, const long long& b, const long long& c, const std::vector<std::string>& program);

private:
	long long getCombo(int operand);

	void adv(int operand);
	void bxl(int operand);
	void bst(int operand);
	void jnz(int operand);
	void bxc(int operand);
	void out(int operand);
	void bdv(int operand);
	void cdv(int operand);

	long long a, b, c;
	std::vector<int> program;
	int instructionPointer;
	std::string output;
};

Computer::Computer() {
	a = b = c = 0;
	instructionPointer = 0;
}

std::string Computer::run(const long long& a, const long long& b, const long long& c, const std::vector<std::string>& program) {
	this->a = a;
	this->b = b;
	this->c = c;
	instructionPointer = 0;
	output = "";
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
			out(operand);
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

	if (output.size() > 0) {
		output.erase(output.begin() + output.size() - 1);
	}
	return output;
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
	a = a / (static_cast<long long>(2) << (getCombo(operand) - 1));
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

void Computer::out(int operand) {
	output += std::to_string(getCombo(operand) & 7) + ",";
	instructionPointer += 2;
}

void Computer::bdv(int operand) {
	b = a / (static_cast<long long>(2) << (getCombo(operand) - 1));
	instructionPointer += 2;
}

void Computer::cdv(int operand) {
	c = a / (static_cast<long long>(2) << (getCombo(operand) - 1));
	instructionPointer += 2;
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

	//std::cout << "Part 2: " <<  << "\n";
	//Utils::copy();
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}