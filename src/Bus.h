#pragma once

#include <cstdint>
#include <array>

#include "nesCPU.h"

class Bus {
    public:
        Bus();
        ~Bus();
    public:
        std::array<uint8_t, 64 * 1024> ram;
        nesCPU cpu;
    public:
        // write data to memory
        void write(uint16_t addr, uint8_t data);
        // read data from memory
        uint8_t read(uint16_t addr, bool readOnly = false);
};