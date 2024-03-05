// CPU.h - Header file for the CPU class
#include "Memory.h"
#ifndef CPU_H
#define CPU_H

class CPU {
public:
    CPU(Memory* memory); // Constructor now expects a pointer to a Memory instance
    ~CPU(); // Destructor

    void executeInstruction(unsigned char opcode); // Execute an instruction based on the opcode

    void run();
    
	unsigned short programCounter = 0; // program counter

private:
    Memory* memory; // Pointer to the Memory instance
	bool running = false; // True if running
    bool zeroFlag = false; // Flag to track comparison results
    // Define CPU registers here. For simplicity, let's assume 8-bit registers.
    unsigned char accumulator; // Example accumulator register
    // Add more registers here as needed.
    unsigned char fetchNextByte();
};

#endif // CPU_H
