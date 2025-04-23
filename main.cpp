#include <bitset>
#include <iostream>

#include "Emulator.h"
#include "Chip8OpCodes.cpp"
#include "OpcodeTree/OpcodeTreeNode.h"
#include "OpcodeTree/OpcodeTree.h"

void test() {
    std::cout << "Trying to call opcode handler for " << std::endl;
}

int main(const int argc, const char * argv[]) {
    // if (argc != 4)
    // {
    //     std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
    //     std::exit(EXIT_FAILURE);
    // }
    //
    // int videoScale = std::stoi(argv[1]);
    // int cycleDelay = std::stoi(argv[2]);
    // char const* romFilename = argv[3];
    std::string rom_filename = "test_opcode.ch8";
    int cycle_delay = 1;

    if (argc == 3) {
        rom_filename = argv[1];
        cycle_delay = std::stoi(argv[2]);
    }

    ROM test_rom {rom_filename};

    Emulator emulator;
    emulator.LoadROM(test_rom);
    emulator.SetCycleDelay(cycle_delay);
    emulator.StartLoop();


    // OpcodeTree ot;
    // ot.Insert("1===", []() {test();});
    // ot.ExecuteOpcode(0x1FFF);


    return 0;
}
