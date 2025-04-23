//
// Created by gaudium on 14.01.2025.
//
#include "Font.h"

FontCharacter Zero{
    {
        0b01100000,
        0b10110000,
        0b10010000,
        0b11010000,
        0b01100000,
    }
};

FontCharacter One{
        {
            0b01000000,
            0b11000000,
            0b01000000,
            0b01000000,
            0b11100000,
        }
};

FontCharacter Two{
    {
        0b11110000,
        0b00010000,
        0b01100000,
        0b10000000,
        0b11110000,
    }
};

FontCharacter Three{
    {
        0b11110000,
        0b00010000,
        0b01100000,
        0b00010000,
        0b11110000,
    }
};

FontCharacter Four{
    {
        0b01010000,
        0b10010000,
        0b11110000,
        0b00010000,
        0b00010000,
    }
};

FontCharacter Five{
    {
        0b11110000,
        0b10000000,
        0b01100000,
        0b00010000,
        0b11110000,
    }
};

FontCharacter Six{
    {
        0b01110000,
        0b10000000,
        0b11110000,
        0b10010000,
        0b11110000,
    }
};

FontCharacter Seven{
    {
        0b11110000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b01000000,
    }
};

FontCharacter Eight{
    {
        0b11100000,
        0b10010000,
        0b11110000,
        0b10010000,
        0b01110000,
    }
};

FontCharacter Nine{
    {
        0b11110000,
        0b10010000,
        0b11110000,
        0b00010000,
        0b01110000,
    }
};

FontCharacter A{
    {
        0b00110000,
        0b01010000,
        0b10010000,
        0b11110000,
        0b10010000,
    }
};

FontCharacter B{
    {
        0b11100000,
        0b10100000,
        0b11110000,
        0b10010000,
        0b11110000,
    }
};

FontCharacter C{
    {
        0b01100000,
        0b10010000,
        0b10000000,
        0b10010000,
        0b01100000,
    }
};

FontCharacter D{
    {
        0b11000000,
        0b10100000,
        0b10010000,
        0b10010000,
        0b11100000,
    }
};

FontCharacter E{
    {
        0b11110000,
        0b10000000,
        0b11100000,
        0b10000000,
        0b11110000,
    }
};

FontCharacter F{
    {
        0b11110000,
        0b10000000,
        0b11100000,
        0b10000000,
        0b10000000,
    }
};

Font DefaultFont{{Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, A, B, C, D, E, F}};
