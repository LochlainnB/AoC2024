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
	Gate* input;
	std::vector<Gate*> outputs;

	void setValue(bool value, int tag = 0);
};

struct Gate {
	GateType type;
	std::pair<Wire*, Wire*> inputs;
	Wire* output;
	int tag;

	void tryActivate(int tag = 0) {
		if (inputs.first->ready && inputs.second->ready) {
			this->tag = tag;
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
			output->setValue(value);
		}
	}
};

struct Circuit {
	std::map<std::string, Wire*> wires;
	std::map<std::string, bool> initialValues;
	long long x;
	long long y;
	std::vector<Gate*> gates;
	std::vector<std::string> swappedWires;

	long long run() {
		for (auto it = wires.begin(); it != wires.end(); it++) {
			it->second->ready = it->second->value = 0;
		}

		for (auto it = initialValues.begin(); it != initialValues.end(); it++) {
			wires[it->first]->setValue(it->second);
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
		return result;
	}

	// Returns true if fault was found
	bool runFirstNBits(int bits) {
		for (auto it = wires.begin(); it != wires.end(); it++) {
			it->second->ready = it->second->value = 0;
		}
		for (int i = 0; i < bits; i++) {
			std::string wire = (i < 10 ? "x0" : "x") + std::to_string(i);
			wires[wire]->setValue(initialValues[wire], i);
			wire = (i < 10 ? "y0" : "y") + std::to_string(i);
			wires[wire]->setValue(initialValues[wire], i);
			std::string zWire = (i < 10 ? "z0" : "z") + std::to_string(i);
			if (!wires[zWire]->ready || (x + y >> i & 1) != wires[zWire]->value) {
				return true;
			}
		}

		for (auto it = wires.begin(); it != wires.end(); it++) {
			it->second->ready = it->second->value = 0;
		}
		for (int i = 0; i < bits; i++) {
			std::string wire = (i < 10 ? "x0" : "x") + std::to_string(i);
			wires[wire]->setValue(i % 2, i);
			wire = (i < 10 ? "y0" : "y") + std::to_string(i);
			wires[wire]->setValue(i % 2, i);
			std::string zWire = (i < 10 ? "z0" : "z") + std::to_string(i);
			if (!wires[zWire]->ready || (0b101010101010101010101010101010101010101010101 + 0b101010101010101010101010101010101010101010101 >> i & 1) != wires[zWire]->value) {
				return true;
			}
		}

		return false;
	}

	bool checkNextLinks(std::queue<GateType> path, Wire* position, Wire* goal) {
		if (position == goal) return true;
		if (position->input == nullptr || path.empty()) return false;

		Gate* input = position->input;
		if (input->type != path.front()) return false;

		std::queue<GateType> newPath = path;
		newPath.pop();
		return checkNextLinks(newPath, input->inputs.first, goal) || checkNextLinks(newPath, input->inputs.second, goal);
	}

	bool zBroken(int z) {
		std::queue<GateType> aPath;
		aPath.push(XOR);
		aPath.push(XOR);
		if (!checkNextLinks(aPath, wires[(z < 10 ? "z0" : "z") + std::to_string(z)], wires[(z < 10 ? "x0" : "x") + std::to_string(z)])) {
			return true;
		}
		std::queue<GateType> bPath = aPath;
		if (!checkNextLinks(aPath, wires[(z < 10 ? "z0" : "z") + std::to_string(z)], wires[(z < 10 ? "y0" : "y") + std::to_string(z)])) {
			return true;
		}

		// Assume first carry works (it does (I think))
		for (int i = z - 1; i >= 1; i--) {
			std::queue<GateType> cPath;
			cPath.push(XOR);
			for (int j = i; j < z; j++) {
				cPath.push(OR);
				cPath.push(AND);
			}

			if (!checkNextLinks(cPath, wires[(z < 10 ? "z0" : "z") + std::to_string(z)], wires[(i < 10 ? "x0" : "x") + std::to_string(i)])) {
				return true;
			}
			if (!checkNextLinks(cPath, wires[(z < 10 ? "z0" : "z") + std::to_string(z)], wires[(i < 10 ? "y0" : "y") + std::to_string(i)])) {
				return true;
			}
		}

		return false;
	}

	void fixCircuit() {
		for (int i = 1; i < 45; i++) {
			if (zBroken(i)) {
				bool resolved = false;
				for (int j = 0; j < gates.size(); j++) {
					for (int k = 0; k < gates.size(); k++) {
						Wire* temp = gates[j]->output;
						gates[j]->output = gates[k]->output;
						gates[k]->output = temp;
						gates[j]->output->input = gates[j];
						gates[k]->output->input = gates[k];
						if (zBroken(i)) {
							temp = gates[j]->output;
							gates[j]->output = gates[k]->output;
							gates[k]->output = temp;
							gates[j]->output->input = gates[j];
							gates[k]->output->input = gates[k];
						}
						else {
							resolved = true;
							swappedWires.push_back(gates[j]->output->id);
							swappedWires.push_back(gates[k]->output->id);
							j = gates.size();
							k = gates.size();
						}
					}
				}
				if (!resolved) {
					std::cout << "ahhhhhh there's a problem with the final bit or a single bit has multiple faults";
				}
			}
		}
	}
};

void Wire::setValue(bool value, int tag) {
	if (ready) {
		// Loop created, abort
		return;
	}
	this->value = value;
	ready = true;
	for (Gate* gate : outputs) {
		gate->tryActivate(tag);
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
	Circuit circuit;
	for (int i = 0; i < connections.size(); i++) {
		Gate* newGate = new Gate();
		circuit.gates.push_back(newGate);
		if (connections[i][1] == "AND") newGate->type = AND;
		else if (connections[i][1] == "OR") newGate->type = OR;
		else newGate->type = XOR;

		if (!circuit.wires.count(connections[i][0])) {
			circuit.wires[connections[i][0]] = new Wire{ connections[i][0], 0, 0 };
		}
		newGate->inputs.first = circuit.wires[connections[i][0]];
		circuit.wires[connections[i][0]]->outputs.push_back(newGate);
		if (!circuit.wires.count(connections[i][2])) {
			circuit.wires[connections[i][2]] = new Wire{ connections[i][2], 0, 0 };
		}
		newGate->inputs.second = circuit.wires[connections[i][2]];
		circuit.wires[connections[i][2]]->outputs.push_back(newGate);
		if (!circuit.wires.count(connections[i][4])) {
			circuit.wires[connections[i][4]] = new Wire{ connections[i][4], 0, 0 };
		}
		newGate->output = circuit.wires[connections[i][4]];
		circuit.wires[connections[i][4]]->input = newGate;
	}

	circuit.x = 0;
	circuit.y = 0;
	for (int i = 0; i < initialStates.size(); i++) {
		circuit.initialValues[initialStates[i][0]] = std::stoi(initialStates[i][1]);
		if (initialStates[i][0][0] == 'x') {
			circuit.x |= std::stoll(initialStates[i][1]) << std::stoi(initialStates[i][0].substr(1));
		}
		else if (initialStates[i][0][0] == 'y') {
			circuit.y |= std::stoll(initialStates[i][1]) << std::stoi(initialStates[i][0].substr(1));
		}
	}

	long long result = circuit.run();

	std::cout << "Part 1: " << result << "\n";
	Utils::copy(result);

	// Part 2
	if (file == "Input.txt") {
		circuit.fixCircuit();
		std::cout << circuit.x << " + " << circuit.y << " = " << circuit.run() << "\n";
		long long x = 0b0101010101010101;
		long long y = 0b0101010101010101;
		for (int i = 0; i < 45; i++) {
			circuit.initialValues[initialStates[i][0]] = x >> i & 1;
			circuit.initialValues[initialStates[i+45][0]] = y >> i & 1;
		}
		circuit.x = x;
		circuit.y = y;
		std::cout << circuit.x << " + " << circuit.y << " = " << circuit.run() << "\n";
		std::sort(circuit.swappedWires.begin(), circuit.swappedWires.end());
		std::string resultStr;
		for (int i = 0; i < circuit.swappedWires.size(); i++) {
			resultStr += circuit.swappedWires[i] + ",";
		}
		resultStr.erase(resultStr.end() - 1);

		std::cout << "Part 2: " << resultStr << "\n";
		Utils::copy(resultStr);
	}
}

int main() {
	std::cout << "Test data results:\n";
	solution("Test.txt");
	std::cout << "Puzzle input results:\n";
	solution("Input.txt");
}