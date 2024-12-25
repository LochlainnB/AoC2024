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

enum GateType { AND, OR, XOR };

struct Gate;

struct Wire {
	std::string id;
	bool value;
	bool ready;
	std::vector<Gate*> outputs;

	void setValue(bool value);
};

struct Gate {
	GateType type;
	std::pair<Wire*, Wire*> inputs;
	std::vector<Wire*> outputs;

	void tryActivate() {
		if (inputs.first->ready && inputs.second->ready) {
			bool value = false;
			switch (type) {
			case AND:
				value = inputs.first->value && inputs.second->value;
				break;
			case OR:
				value = inputs.first->value || inputs.second->value;
				break;
			case XOR:
				value = inputs.first->value ^ inputs.second->value;
				break;
			}
			for (Wire* output : outputs) {
				output->setValue(value);
			}
		}
	}
};

void Wire::setValue(bool value) {
	this->value = value;
	ready = true;
	for (Gate* gate : outputs) {
		gate->tryActivate();
	}
}

void solution(std::string file) {
	std::string rawInput = Utils::loadFile(file);
	std::vector<std::string> blocks = Utils::split(rawInput, "\n\n");
	// Use lines for 1D vector
	std::vector<std::string> initialStateLines = Utils::split(blocks[0], "\n");
	std::vector<std::string> connectionLines = Utils::split(blocks[1], "\n");
	// Use input for 2D vector
	std::vector<std::vector<std::string>> initialStates;
	for (int i = 0; i < initialStateLines.size(); i++) {
		initialStates.push_back(Utils::split(initialStateLines[i], ": "));
	}
	std::vector<std::vector<std::string>> connections;
	for (int i = 0; i < connectionLines.size(); i++) {
		connections.push_back(Utils::split(connectionLines[i], " "));
	}

	// Part 1
	std::map<std::string, Wire*> wires;
	std::vector<Gate*> gates;
	for (int i = 0; i < connections.size(); i++) {
		Gate* newGate = new Gate();
		gates.push_back(newGate);
		if (connections[i][1] == "AND") newGate->type = AND;
		else if (connections[i][1] == "OR") newGate->type = OR;
		else newGate->type = XOR;

		if (!wires.count(connections[i][0])) {
			wires[connections[i][0]] = new Wire{ connections[i][0], 0, 0 };
		}
		newGate->inputs.first = wires[connections[i][0]];
		wires[connections[i][0]]->outputs.push_back(newGate);
		if (!wires.count(connections[i][2])) {
			wires[connections[i][2]] = new Wire{ connections[i][2], 0, 0 };
		}
		newGate->inputs.second = wires[connections[i][2]];
		wires[connections[i][2]]->outputs.push_back(newGate);
		if (!wires.count(connections[i][4])) {
			wires[connections[i][4]] = new Wire{ connections[i][4], 0, 0 };
		}
		newGate->outputs.push_back(wires[connections[i][4]]);
	}

	for (int i = 0; i < initialStates.size(); i++) {
		wires[initialStates[i][0]]->setValue(std::stoi(initialStates[i][1]));
	}

	int zValue = 0;
	bool done = false;
	long long result = 0;
	while (!done) {
		std::string wire = (zValue < 10 ? "z0" : "z") + std::to_string(zValue);
		if (wires.count(wire)) {
			result |= static_cast<long long>(wires[wire]->value) << zValue;
		}
		else done = true;
		zValue++;
	}

	std::cout << "Part 1: " << result << "\n";
	Utils::copy(result);

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