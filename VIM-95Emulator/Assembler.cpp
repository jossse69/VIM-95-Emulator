#include "Assembler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

Assembler::Assembler() {}

Assembler::~Assembler() {}

bool Assembler::loadAssemblyFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    std::map<std::string, int> labelAddresses;
    std::vector<std::pair<std::string, std::string>> instructions; // To store instructions and their operands (if any)
    std::string line;
    int address = 0;

    // First Pass: Identify labels and their addresses
    while (getline(file, line)) {
        // Remove comments
        size_t commentPos = line.find(';');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        if (line.empty()) continue; // Skip empty lines

        std::istringstream iss(line);
        std::string word;
        iss >> word;

        // Check for label
        if (word.back() == ':') {
            std::string label = word.substr(0, word.length() - 1);
            labelAddresses[label] = address;
        }
        else {
            std::string operand = "";
            if (iss >> operand) { // Attempt to read an operand
                address += 2; // Assuming each instruction+operand pair is 2 bytes
                instructions.push_back({ word, operand });
            }
            else {
                address += 1; // Instruction only
                instructions.push_back({ word, "" });
            }
        }
    }

    // Second Pass: Assemble instructions, substituting labels with addresses
    for (const auto& instr : instructions) {
        unsigned char opcode = parseInstruction(instr.first);
        machineCode.push_back(opcode);

        if (!instr.second.empty()) {
            // Check if operand is a label
            if (labelAddresses.find(instr.second) != labelAddresses.end()) {
                int labelAddress = labelAddresses[instr.second];
                machineCode.push_back(static_cast<unsigned char>(labelAddress));
            }
            else {
                // Assume it's a direct value or address
                machineCode.push_back(std::stoi(instr.second, nullptr, 16));
            }
        }
    }

    file.close();
    return true;
}

unsigned char Assembler::parseInstruction(const std::string& instruction) {
    // Instruction to opcode mapping
    if (instruction == "NOP") {
        return 0x00; // No operation
    }
    else if (instruction == "LDA") {
        return 0x01; // Load Accumulator
    }
    else if (instruction == "STA") {
        return 0x02; // Store Accumulator
    }
    else if (instruction == "ADD") {
        return 0x03; // Add to Accumulator
    }
    else if (instruction == "JMP") {
        return 0x04; // Jump to Address
    }
	else if (instruction == "CMP")
		return 0x05; // Compare Accumulator
    else if (instruction == "JEQ") {
		return 0x06; // Jump to Address if ZeroFlag is set
    }

	else if (instruction == "HALT")
		return 0xFF; // Halt

    return 0xFF; // Unknown instruction
}

const std::vector<unsigned char>& Assembler::getMachineCode() const {
    return machineCode;
}
