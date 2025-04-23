//
// Created by gaudium on 13.01.2025.
//
#include <cstring>

#include "Chip8.h"

// SYS addr - Jump to a machine code routine at nnn.
void Chip8::OP_0nnn() {
    // This instruction is only used on the old computers on which Chip-8 was originally implemented.
    // It is ignored by modern interpreters.
}

// CLS - Clear the display.
void Chip8::OP_00E0() {
    memset(display, 0, sizeof(display));
}

// RET - Return from a subroutine.
void Chip8::OP_00EE() {
    --stack_pointer;
    program_counter = stack[stack_pointer];
}

// JP addr - Jump to location nnn.
void Chip8::OP_1nnn() {
    const uint16_t address = opcode & 0x0FFFu;
    program_counter = address;
}

// CALL addr - Call subroutine at nnn.
void Chip8::OP_2nnn() {
    stack[stack_pointer] = program_counter;
    ++stack_pointer;

    uint16_t address = opcode & 0x0FFFu;
    program_counter = address;
}

// SE Vx, byte - Skip next instruction if Vx = kk.
void Chip8::OP_3xkk() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];
    const uint8_t kk = opcode & 0x00FFu;

    if (Vx == kk)
        program_counter += 2;
}

// SNE Vx, byte - Skip next instruction if Vx != kk.
void Chip8::OP_4xkk() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];
    const uint8_t kk = opcode & 0x00FFu;

    if (Vx != kk)
        program_counter += 2;
}

// SE Vx, Vy - Skip next instruction if Vx = Vy.
void Chip8::OP_5xy0() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];
    const uint8_t Vy = registers[(opcode & 0x00F0u) >> 4];

    if (Vx == Vy)
        program_counter += 2;
}

// LD Vx, byte - Set Vx = kk.
void Chip8::OP_6xkk() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t kk = opcode & 0x00FFu;

    registers[x] = kk;
}

// ADD Vx, byte - Set Vx = Vx + kk.
void Chip8::OP_7xkk() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t kk = opcode & 0x00FFu;

    registers[x] += kk;
}

// LD Vx, Vy - Set Vx = Vy.
void Chip8::OP_8xy0() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t y = (opcode & 0x00F0u) >> 4;

    registers[x] = registers[y];
}

// OR Vx, Vy - Set Vx = Vx OR Vy.
void Chip8::OP_8xy1() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t y = (opcode & 0x00F0u) >> 4;

    registers[x] |= registers[y];
}

// AND Vx, Vy - Set Vx = Vx AND Vy.
void Chip8::OP_8xy2() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t y = (opcode & 0x00F0u) >> 4;

    registers[x] &= registers[y];
}

// XOR Vx, Vy - Set Vx = Vx XOR Vy.
void Chip8::OP_8xy3() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t y = (opcode & 0x00F0u) >> 4;

    registers[x] ^= registers[y];
}

// ADD Vx, Vy - Set Vx = Vx + Vy, set VF = carry.
void Chip8::OP_8xy4() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t y = (opcode & 0x00F0u) >> 4;

    uint16_t sum = registers[x] + registers[y];
    registers[0xF] = sum > 1;
    registers[x] = sum & 0xFFu;
}

// SUB Vx, Vy - Set Vx = Vx - Vy, set VF = NOT borrow.
void Chip8::OP_8xy5() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t y = (opcode & 0x00F0u) >> 4;

    registers[0xF] = registers[x] > registers[y];

    registers[x] -= registers[y];
}

// SHR Vx {, Vy} - Set Vx = Vx SHR 1.
void Chip8::OP_8xy6() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;

    registers[0xF] = registers[x] & 0x1u;
    registers[x] >>= 1;
}

// SUBN Vx, Vy - Set Vx = Vy - Vx, set VF = NOT borrow.
void Chip8::OP_8xy7() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t y = (opcode & 0x00F0u) >> 4;

    registers[0xF] = registers[y] > registers[x];

    registers[x] = registers[y] - registers[x];
}

// SHL Vx {, Vy} - Set Vx = Vx SHL 1.
void Chip8::OP_8xyE() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;

    registers[0xF] = (registers[x] & 0x80u) >> 7;

    registers[x] <<= 1;
}

// SNE Vx, Vy - Skip next instruction if Vx != Vy.
void Chip8::OP_9xy0() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];
    const uint8_t Vy = registers[(opcode & 0x00F0u) >> 4];

    if (Vx != Vy)
        program_counter += 2;
}

// LD I, addr - Set I = nnn.
void Chip8::OP_Annn() {
    const uint16_t address = opcode & 0x0FFFu;

    index_register = address;
}

// JP V0, addr - Jump to location nnn + V0.
void Chip8::OP_Bnnn() {
    const uint16_t address = opcode & 0x0FFFu;

    program_counter = address + registers[0x0];
}

// RND Vx, byte - Set Vx = random byte AND kk.
void Chip8::OP_Cxkk() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;
    const uint8_t kk = opcode & 0x00FFu;

    registers[x] = ReadRandomByte() & kk;
}

// TODO: may have bugs
// DRW Vx, Vy, nibble - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void Chip8::OP_Dxyn() {
    const uint8_t coord_x = registers[(opcode & 0x0F00u) >> 8];
    const uint8_t coord_y = registers[(opcode & 0x00F0u) >> 4];
    const uint8_t n = opcode & 0x000Fu;

    auto sprite = ReadFromMemory(index_register, n);
    registers[0xF] = DrawSprite(sprite, coord_x, coord_y);
}

// SKP Vx - Skip next instruction if key with the value of Vx is pressed.
void Chip8::OP_Ex9E() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];

    if (keypad[Vx])
        program_counter += 2;
}

// SKNP Vx - Skip next instruction if key with the value of Vx is not pressed.
void Chip8::OP_ExA1() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];

    if (!keypad[Vx])
        program_counter += 2;
}

// LD Vx, DT - Set Vx = delay timer value.
void Chip8::OP_Fx07() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;

    registers[x] = delay_timer;
}

// LD Vx, K - Wait for a key press, store the value of the key in Vx.
void Chip8::OP_Fx0A() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;

    int key;
    do {
        key = AnyKeyPressed();
        program_counter -= 2; // wait
    } while (key == -1);

    registers[x] = static_cast<uint8_t>(key);
}

// LD DT, Vx - Set delay timer = Vx.
void Chip8::OP_Fx15() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];

    delay_timer = Vx;
}

// LD ST, Vx - Set sound timer = Vx.
void Chip8::OP_Fx18() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];

    sound_timer = Vx;
}

// ADD I, Vx - Set I = I + Vx.
void Chip8::OP_Fx1E() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];

    index_register += Vx;
}

// LD F, Vx - Set I = location of sprite for digit Vx.
void Chip8::OP_Fx29() {
    const uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];
    const uint16_t address = FONT_START_ADDRESS + Vx * CHARACTER_BYTES_COUNT;

    index_register = address;
}

// LD B, Vx - Store BCD representation of Vx in memory locations I, I+1, and I+2.
void Chip8::OP_Fx33() {
    uint8_t Vx = registers[(opcode & 0x0F00u) >> 8];

    memory[index_register + 2] = Vx % 10;
    Vx /= 10;

    memory[index_register + 1] = Vx % 10;
    Vx /= 10;

    memory[index_register] = Vx % 10;
}

// LD [I], Vx - Store registers V0 through Vx in memory starting at location I.
void Chip8::OP_Fx55() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;

    std::vector<uint8_t> bytes(x+1);
    for (uint8_t i = 0; i <= x; i++)
        bytes[i] = registers[i];

    CopyToMemory(index_register, bytes);
}

// LD Vx, [I] - Read registers V0 through Vx from memory starting at location I.
void Chip8::OP_Fx65() {
    const uint8_t x = (opcode & 0x0F00u) >> 8;

    auto bytes = ReadFromMemory(index_register, x+1);
    for (uint8_t i = 0; i <= x; i++)
        registers[i] = bytes[i];
}

// Method that invokes when invalid opcode received
void Chip8::OP_NULL() {

}
