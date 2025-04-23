//
// Created by gaudium on 13.01.2025.
//

#ifndef FONT_H
#define FONT_H

#include <cstdint>
#include <vector>

inline constexpr int FONT_CHARACTERS_COUNT = 16;
inline constexpr int CHARACTER_BYTES_COUNT = 5;
inline uint16_t FONT_START_ADDRESS = 0x050;


struct FontCharacter {
    uint8_t bytes[CHARACTER_BYTES_COUNT]{};
};

struct Font {
    FontCharacter chars[FONT_CHARACTERS_COUNT];

    [[nodiscard]] std::vector<uint8_t> GetByteArray() const {
        constexpr int byte_count = FONT_CHARACTERS_COUNT * CHARACTER_BYTES_COUNT;
        std::vector<uint8_t> result(byte_count);

        for (int i = 0; i < byte_count; i++) {
            result[i] = chars[i / 5].bytes[i % 5];
        }

        return result;
    }
};


extern FontCharacter Zero;

extern FontCharacter One;

extern FontCharacter Two;

extern FontCharacter Three;

extern FontCharacter Four;

extern FontCharacter Five;

extern FontCharacter Six;

extern FontCharacter Seven;

extern FontCharacter Eight;

extern FontCharacter Nine;

extern FontCharacter A;

extern FontCharacter B;

extern FontCharacter C;

extern FontCharacter D;

extern FontCharacter E;

extern FontCharacter F;

extern Font DefaultFont;

#endif //FONT_H
