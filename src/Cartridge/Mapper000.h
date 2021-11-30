#pragma once

#include <vector>
#include "types.h"

using namespace std;

class Mapper000 {
    public:
        Mapper000(
            mirrorType _mirror,
            vector<uint8_t> PRGROMData
        );
        ~Mapper000();

        uint8_t CPUread(uint16_t address);
        void CPUwrite(uint16_t address, uint8_t write);
        uint8_t PPUread(uint16_t address);
        void PPUwrite(uint16_t address, uint8_t write);

        string ROMName = "NROM";
    private:
        uint8_t PRGROMSize;
        mirrorType mirror;
        vector<uint8_t> PRGROM, CHRRAM;       
};
