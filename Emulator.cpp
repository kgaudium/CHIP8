//
// Created by gaudium on 13.01.2025.
//
#include "Emulator.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void Emulator::LoadROM(const ROM &rom) {
    rom.LoadToChip8(chip8);
}

void Emulator::LoadFont(const Font &font) {
    chip8.CopyToMemory(FONT_START_ADDRESS, font.GetByteArray());
}

void Emulator::SetCycleDelay(const int new_value) {
    if (new_value < 0)
        throw std::invalid_argument("Cycle Delay cannot be lower than zero! Passed new_value: " + new_value);

    cycle_delay = new_value;
}
