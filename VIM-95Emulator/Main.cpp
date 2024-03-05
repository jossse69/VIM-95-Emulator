#include <iostream>
#include "CPU.h"
#include "Assembler.h"
#include "Memory.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <assembly_file.asm>" << std::endl;
        return 1;
    }

    std::string asmFilename = argv[1]; // Get the assembly file name from the command line

    // Create a Memory instance with a specific size
    unsigned int memorySize = 1024; // Example size, adjust as needed
    Memory memory(memorySize);

    Assembler assembler;
    if (!assembler.loadAssemblyFile(asmFilename)) { // Load the specified assembly file
        std::cerr << "Failed to load assembly file: " << asmFilename << std::endl;
        return 1;
    }

    const std::vector<unsigned char>& machineCode = assembler.getMachineCode();

    // Load the machine code into memory
    for (size_t address = 0; address < machineCode.size(); ++address) {
        memory.write(address, machineCode[address]);
    }

    // Create a CPU instance, passing a pointer to the Memory instance
    CPU cpu(&memory);

    std::cout << "Starting VIM-95 Emulator..." << std::endl;

    cpu.run(); // Run the CPU

    std::cout << std::endl;
    std::cout << "Execution finished." << std::endl;
    std::cout << "Press enter to close." << std::endl;
    getchar();

    return 0;
}
