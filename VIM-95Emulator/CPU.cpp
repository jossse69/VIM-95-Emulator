// CPU.cpp - Implementation file for the CPU class
#include "CPU.h"
#include <iostream>

CPU::CPU(Memory* memory) : memory(memory) {
    // Initialization
}

CPU::~CPU() {
    // Cleanup resources if needed
}

unsigned char CPU::fetchNextByte() {
    // Implementation that reads the next byte from memory
    unsigned char byte = memory->read(programCounter);
    programCounter++;
    return byte;
}

void CPU::executeInstruction(unsigned char opcode) {
    switch (opcode) {
    case 0x00: // NOP: No operation
        // Do nothing
        break;
    case 0x01: // LDA: Load Accumulator
        // Example: Load the next byte into the accumulator
        accumulator = fetchNextByte();
        break;
    case 0x02: // STA: Store Accumulator
        // Example: Store the accumulator in the next memory location
        memory->write(fetchNextByte(), accumulator);
        break;
    case 0x03: // ADD: Add to Accumulator
        // Example: Add the next byte to the accumulator
        accumulator += fetchNextByte();
        break;
    case 0x04: // JMP: Jump to Address
        // Example: Set the program counter to the next byte
        programCounter = fetchNextByte();
        break;
    case 0x05: // CMP: Compare Accumulator with Next Byte
    {
        unsigned char value = fetchNextByte();
        zeroFlag = (accumulator == value);
    }
    break;
    case 0x06: // JEQ: Jump if Equal
        if (zeroFlag) {
            programCounter = fetchNextByte(); // Jump to address
        }
        else {
            programCounter++; // Skip the address byte if not jumping
        }
        break;
	case 0xFF: // HALT: Halts the program counter
		// Example: Set the program counter to a value greater than the memory limit
        running = false;
		break;
    default:
        // Unknown opcode handling
        std::cerr << "Unknown opcode: " << std::hex << static_cast<int>(opcode) << std::endl;
        break;
    }
}

void CPU::run() {
    running = true;
    while (running) {
        unsigned char opcode = fetchNextByte(); // Fetch the next instruction based on the program counter

		// if we are outside of the memory range, then halt
        if (programCounter >= memory->getSize()) {
            running = false;
            break;
        }

        executeInstruction(opcode); // Execute the fetched instruction
    }
}
