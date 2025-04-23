//
// Created by gaudium on 13.01.2025.
//
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>

#ifndef EMULATOR_H
#define EMULATOR_H

#include "Font.h"

#include "Chip8.h"
#include "ROM.h"

class Emulator {
    Chip8 chip8;
    Font font;
    int cycle_delay = 10;

public:
    Emulator() {
        font = DefaultFont;
        // chip8 = Chip8();
        LoadFont(font);
    }

    void LoadROM(const ROM &rom);

    void LoadFont(const Font &font);

    void SetCycleDelay(int new_value);

    void StartLoop() {
        auto lastCycleTime = std::chrono::high_resolution_clock::now();
        bool quit = false;

        while (!quit) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();


            // usleep(cycle_delay);
            if (dt > cycle_delay)
            {
                lastCycleTime = currentTime;

                chip8.DoCycle();
            }
        }
    }
};


#endif //EMULATOR_H
