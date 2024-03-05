#include "Memory.h"
#include <iostream>

Memory::Memory(unsigned int size) : data(size, 0) {
    // Initialize memory with a given size, default value is 0
}

Memory::~Memory() {
    // Destructor, if needed for cleanup
}

unsigned char Memory::read(unsigned int address) const {
    if (address < data.size()) {
        return data[address];
    }
    else {
        // Handle invalid address access
        // For simplicity, return 0, but consider logging or throwing an exception
        return 0;
    }
}

void Memory::write(unsigned int address, unsigned char value) {
    if (address == 0xFF) {
        // Handle output
        std::cout << static_cast<char>(value);
    }
    else if (address < data.size()) {
        data[address] = value;
    }
    else {
        // Handle invalid address access
    }
}
