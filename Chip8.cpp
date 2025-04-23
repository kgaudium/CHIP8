//
// Created by gaudium on 13.01.2025.
//

#include "Chip8.h"

#include <unistd.h>

void Chip8::CopyToMemory(uint16_t start_address, const std::vector<uint8_t> &data) {
    for (const auto & byte : data) {
        memory[start_address] = byte;
        start_address++;
    }
}

void Chip8::CopyToMemory(const std::vector<uint8_t> &data) {
    CopyToMemory(0, data);
}

std::vector<uint8_t> Chip8::ReadFromMemory(uint16_t start_address, uint16_t bytes_count) const {
    std::vector<uint8_t> result(bytes_count);
    for (int i = 0; i < bytes_count; i++) {
        result[i] = memory[start_address + i];
    }

    return result;
}

bool Chip8::DrawSprite(const std::vector<uint8_t> &sprite, const uint8_t coord_x, const uint8_t coord_y) {
    bool erased_flag = false;

    for (int x_screen = coord_x, x_sprite=0; x_sprite < 8; x_screen++, x_sprite++) {
        for (int y_screen = coord_y, y_sprite=0; y_sprite < sprite.size(); y_screen++, y_sprite++) {
            x_screen %= DISPLAY_WIDTH;
            y_screen %= DISPLAY_HEIGHT;

            if (display[y_screen][x_screen] == 1)
                erased_flag = true;

            display[y_screen][x_screen] = GetBitFromByte(sprite[y_sprite], 7-x_sprite) ^ display[y_screen][x_screen];
        }
    }

    return erased_flag;
}

void Chip8::DoCycle() {
    opcode = memory[program_counter] << 8u | memory[program_counter+1];
    program_counter += 2;

    PrintDisplay();
    ExecuteInstruction(opcode);

    if (delay_timer > 0)
        delay_timer--;

    if (sound_timer > 0)
        sound_timer--;
}
