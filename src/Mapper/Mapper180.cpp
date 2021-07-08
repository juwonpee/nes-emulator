#include <iostream>

#include "types.h"
#include "Mapper/Mapper180.h"

using namespace std;

Mapper180::Mapper180(
    mirrorType _mirror,
    vector<uint8_t> PRGROMData
)
{
    cout << "Mapper180 init" << endl;
    PRGROM = PRGROMData;
    CHRRAM.reserve(8192);
}

uint8_t Mapper180::CPUread(uint16_t address) {
    if (address >= 0x8000 && address < 0xC000) {
        return PRGROM[address];
    }
    else {
        address = address - 0xC000 + PRGROMMapNumber * 16384;
        return PRGROM[address];
    }
    return 0;
}

void Mapper180::CPUwrite(uint16_t address, uint8_t data) {
    if (address >= 0x8000) {
        PRGROMMapNumber = data;
    }
    return;
}

uint8_t Mapper180::PPUread(uint16_t address) {
    if (address < 0x1000) {
        return CHRRAM[address];
    }
    return 0;
}

void Mapper180::PPUwrite(uint16_t address, uint8_t data) {
    // do nothing
}