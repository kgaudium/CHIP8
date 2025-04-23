//
// Created by gaudium on 14.01.2025.
//

#ifndef OPCODETREENODE_H
#define OPCODETREENODE_H
#include <functional>
#include <utility>
#include <vector>


class OpcodeTreeNode {
public:
    bool is_leaf{};

    std::function<void()> opcode_handler;

    std::vector<std::unique_ptr<OpcodeTreeNode> > children{16};
    std::unique_ptr<OpcodeTreeNode> any;

    explicit OpcodeTreeNode(std::function<void()> handler): opcode_handler(std::move(handler)) {
    };

    [[nodiscard]] bool IsHaveChild(const uint8_t symbol) const {
        return children[symbol].get() != nullptr;
    }

    [[nodiscard]] OpcodeTreeNode *GetChild(const uint8_t symbol) {
        return children[symbol].get();
    }

    void AddChild(const uint8_t symbol, const std::function<void()>& handler) {
        if (IsHaveChild(symbol))
            throw std::invalid_argument("Node already have child: " + symbol);

        if (!IsValidSymbol(symbol))
            throw std::invalid_argument("Invalid symbol: " + symbol);

        children[symbol] = std::make_unique<OpcodeTreeNode>(handler);
    }

    void AddChildAny(const std::function<void()>& handler) {
        if (any.get() != nullptr)
            throw std::invalid_argument("Node already have Any child");

        any = std::make_unique<OpcodeTreeNode>(handler);
    }

    void CallHandler() const {
        if (!opcode_handler)
            throw std::runtime_error("Opcode handler is not defined");

        opcode_handler();
    }

    static bool IsValidSymbol(const uint8_t symbol) {
        return symbol <= 0xF;
    }
};


#endif //OPCODETREENODE_H
