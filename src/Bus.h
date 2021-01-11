#pragma once

#include <cstdint>
#include <array>

#include "nes6502.h"

class Bus {
    public:
        Bus();
        ~Bus();
    public:
        std::array<uint8_t, 64 * 1024> ram;
        nes6502 cpu;
    public:
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr, bool readOnly = false);
};