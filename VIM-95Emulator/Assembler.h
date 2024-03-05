#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>

class Assembler {
public:
    Assembler();
    ~Assembler();

    bool loadAssemblyFile(const std::string& filename);
    const std::vector<unsigned char>& getMachineCode() const;

private:
    std::vector<unsigned char> machineCode;

    unsigned char parseInstruction(const std::string& instruction);
    // Add methods for parsing different types of instructions here
};

#endif // ASSEMBLER_H
