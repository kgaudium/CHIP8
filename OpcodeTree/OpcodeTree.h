//
// Created by gaudium on 14.01.2025.
//

#ifndef OPCODETREE_H
#define OPCODETREE_H
#include <cstdint>
#include "OpcodeTreeNode.h"


class OpcodeTree {
    static constexpr uint8_t OPCODE_LENGTH = 4;
    static constexpr char TEMPLATE_CHAR = '=';
    OpcodeTreeNode root;

public:
    OpcodeTree(): root(nullptr) {
    }

    void Insert(const std::string &opcode, const std::function<void()>& handler) {
        if (opcode.length() != OPCODE_LENGTH)
            throw std::invalid_argument(std::format("Given opcode length is: {} but correct is: {}", opcode.length(),
                                                    OPCODE_LENGTH));

        OpcodeTreeNode *temp_node = &root;

        for (auto it = opcode.begin(); it != opcode.end(); ++it) {
            if (*it == TEMPLATE_CHAR) {
                if (temp_node->any == nullptr) {
                    if (it == opcode.end()-1) {
                        temp_node->AddChildAny(handler);
                        temp_node->any->is_leaf = true;
                        break;
                    }

                    temp_node->AddChildAny(nullptr);
                }

                temp_node = temp_node->any.get();
                continue;
            }

            // TODO: may have an impact on performance
            const uint8_t symbol = std::stoi(std::string{*it}, 0, 16);
            if (temp_node->IsHaveChild(symbol)) {
                temp_node = temp_node->GetChild(symbol);
                continue;
            }

            if (it == opcode.end()-1) {
                temp_node->AddChild(symbol, handler);
                temp_node->GetChild(symbol)->is_leaf = true;
                break;
            }

            temp_node->AddChild(symbol, nullptr);
            temp_node = temp_node->GetChild(symbol);
        }
    }

    void ExecuteOpcode(const uint16_t opcode) {
        OpcodeTreeNode *temp_node = &root;

        for (int i = 0; i < OPCODE_LENGTH; i++) {
            if (temp_node == nullptr)
                throw std::invalid_argument("Cannot find opcode: " + opcode);

            const uint8_t symbol = GetOpcodeSymbol(opcode, OPCODE_LENGTH - 1 - i);
            if (temp_node->IsHaveChild(symbol)) {
                temp_node = temp_node->GetChild(symbol);
            }
            else if (temp_node->any != nullptr) {
                temp_node = temp_node->any.get();
            }
            else {
                throw std::invalid_argument("Cannot find opcode: " + std::format("%02X", opcode));
            }
        }

        // std::cout << "Trying to call opcode handler for " << opcode << std::endl;
        // temp_node->opcode_handler();
        temp_node->CallHandler();
    }


    [[nodiscard]] static uint8_t GetOpcodeSymbol(uint16_t opcode, uint8_t symbol_number) {
        return (opcode & 0xF << symbol_number*4) >> symbol_number*4;
    }
};


#endif //OPCODETREE_H
