//
// Created by gaudium on 13.01.2025.
//

#ifndef CHIP8_H
#define CHIP8_H
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>

#include "OpcodeTree/OpcodeTree.h"

#ifndef FONT_H
#include "Font.h"
#endif

inline constexpr uint16_t DEFAULT_PC_VALUE = 0x200;
inline constexpr uint8_t DISPLAY_WIDTH = 64;
inline constexpr uint8_t DISPLAY_HEIGHT = 32;

class Chip8 {
public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index_register{};
    uint16_t program_counter{};
    uint16_t stack[16]{};
    uint8_t stack_pointer{};
    uint8_t delay_timer{};
    uint8_t sound_timer{};
    bool keypad[16]{};
    // TODO with vectors
    bool display[DISPLAY_HEIGHT][DISPLAY_WIDTH]{};
    uint16_t opcode{};

private:
    std::uniform_int_distribution<uint8_t> random_byte;
    std::default_random_engine rand_gen;

    OpcodeTree opcode_tree;

public:
    Chip8() {
        ConfigureOpcodeTree();
        ConfigureRandom();
        SetDefaultState();
    }

    Chip8(const Chip8 &) = delete; // Запрет копирования
    Chip8 &operator=(const Chip8 &) = delete; // Запрет присваивания

    void CopyToMemory(uint16_t start_address, const std::vector<uint8_t> &data);

    void CopyToMemory(const std::vector<uint8_t> &data);

    [[nodiscard]] std::vector<uint8_t> ReadFromMemory(uint16_t start_address, uint16_t bytes_count) const;

    bool DrawSprite(const std::vector<uint8_t> &sprite, uint8_t coord_x, uint8_t coord_y);

    void SetDefaultState() {
        program_counter = DEFAULT_PC_VALUE;
    }

    void ExecuteInstruction(const uint16_t opcode) {
        opcode_tree.ExecuteOpcode(opcode);
    }

    void DoCycle();

private:
    void ConfigureRandom(const long seed = std::chrono::system_clock::now().time_since_epoch().count()) {
        rand_gen = std::default_random_engine(seed);
        random_byte = std::uniform_int_distribution<uint8_t>(0, 255U);
    }

    uint8_t ReadRandomByte() {
        return random_byte(rand_gen);
    }

    int AnyKeyPressed() {
        for (uint8_t i = 0; i < 16; i++) {
            if (keypad[i])
                return i;
        }

        return -1;
    }

    void ConfigureOpcodeTree() {
        opcode_tree = OpcodeTree();
        InsertOpcodesIntoOpcodeTree();
    }

    void PrintDisplay() const {
        std::cout << "\033[2J\033[1;1H"; // clear console

        for (uint8_t y = 0; y < DISPLAY_HEIGHT; ++y) {
            for (uint8_t x = 0; x < DISPLAY_WIDTH; ++x) {
                std::cout << (display[y][x] ? "██" : "  ");
            }
            std::cout << '\n';
        }
    }

    void InsertOpcodesIntoOpcodeTree() {
        auto me = this;
        opcode_tree.Insert("0===", [me]() { me->OP_0nnn(); });
        opcode_tree.Insert("00E0", [me]() { me->OP_00E0(); });
        opcode_tree.Insert("00EE", [me]() { me->OP_00EE(); });
        opcode_tree.Insert("1===", [me]() { me->OP_1nnn(); });
        opcode_tree.Insert("2===", [me]() { me->OP_2nnn(); });
        opcode_tree.Insert("3===", [me]() { me->OP_3xkk(); });
        opcode_tree.Insert("4===", [me]() { me->OP_4xkk(); });
        opcode_tree.Insert("5==0", [me]() { me->OP_5xy0(); });
        opcode_tree.Insert("6===", [me]() { me->OP_6xkk(); });
        opcode_tree.Insert("7===", [me]() { me->OP_7xkk(); });
        opcode_tree.Insert("8==0", [me]() { me->OP_8xy0(); });
        opcode_tree.Insert("8==1", [me]() { me->OP_8xy1(); });
        opcode_tree.Insert("8==2", [me]() { me->OP_8xy2(); });
        opcode_tree.Insert("8==3", [me]() { me->OP_8xy3(); });
        opcode_tree.Insert("8==4", [me]() { me->OP_8xy4(); });
        opcode_tree.Insert("8==5", [me]() { me->OP_8xy5(); });
        opcode_tree.Insert("8==6", [me]() { me->OP_8xy6(); });
        opcode_tree.Insert("8==7", [me]() { me->OP_8xy7(); });
        opcode_tree.Insert("8==E", [me]() { me->OP_8xyE(); });
        opcode_tree.Insert("9==0", [me]() { me->OP_9xy0(); });
        opcode_tree.Insert("A===", [me]() { me->OP_Annn(); });
        opcode_tree.Insert("B===", [me]() { me->OP_Bnnn(); });
        opcode_tree.Insert("C===", [me]() { me->OP_Cxkk(); });
        opcode_tree.Insert("D===", [me]() { me->OP_Dxyn(); });
        opcode_tree.Insert("E=9E", [me]() { me->OP_Ex9E(); });
        opcode_tree.Insert("E=A1", [me]() { me->OP_ExA1(); });
        opcode_tree.Insert("F=07", [me]() { me->OP_Fx07(); });
        opcode_tree.Insert("F=0A", [me]() { me->OP_Fx0A(); });
        opcode_tree.Insert("F=15", [me]() { me->OP_Fx15(); });
        opcode_tree.Insert("F=18", [me]() { me->OP_Fx18(); });
        opcode_tree.Insert("F=1E", [me]() { me->OP_Fx1E(); });
        opcode_tree.Insert("F=29", [me]() { me->OP_Fx29(); });
        opcode_tree.Insert("F=33", [me]() { me->OP_Fx33(); });
        opcode_tree.Insert("F=55", [me]() { me->OP_Fx55(); });
        opcode_tree.Insert("F=65", [me]() { me->OP_Fx65(); });
    }

    static bool GetBitFromByte(const uint8_t byte, const uint8_t bit_number) {
        return (byte & 0x1 << bit_number) >> bit_number;
    }

public:
    void OP_0nnn();

    void OP_00E0();

    void OP_00EE();

    void OP_1nnn();

    void OP_2nnn();

    void OP_3xkk();

    void OP_4xkk();

    void OP_5xy0();

    void OP_6xkk();

    void OP_7xkk();

    void OP_8xy0();

    void OP_8xy1();

    void OP_8xy2();

    void OP_8xy3();

    void OP_8xy4();

    void OP_8xy5();

    void OP_8xy6();

    void OP_8xy7();

    void OP_8xyE();

    void OP_9xy0();

    void OP_Annn();

    void OP_Bnnn();

    void OP_Cxkk();

    void OP_Dxyn();

    void OP_Ex9E();

    void OP_ExA1();

    void OP_Fx07();

    void OP_Fx0A();

    void OP_Fx15();

    void OP_Fx18();

    void OP_Fx1E();

    void OP_Fx29();

    void OP_Fx33();

    void OP_Fx55();

    void OP_Fx65();

    // void OP_();

    void OP_NULL();
};


#endif //CHIP8_H
