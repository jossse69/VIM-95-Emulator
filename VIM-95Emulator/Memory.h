#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

class Memory {
public:
    Memory(unsigned int size); // Constructor to initialize memory with a given size
    ~Memory(); // Destructor

    unsigned int getSize() const { return data.size(); }
    unsigned char read(unsigned int address) const; // Read a byte from a specific memory address
    void write(unsigned int address, unsigned char value); // Write a byte to a specific memory address

private:
    std::vector<unsigned char> data; // Memory storage
};

#endif // MEMORY_H
