#include <iostream>

#include "types.h"
#include "Mapper/Mapper002.h"

using namespace std;

Mapper002::Mapper002(
    mirrorType _mirror,
    vector<uint8_t> PRGROMData
)
{
    cout << "Mapper002 init" << endl;
    mirror = _mirror;
    PRGROM = PRGROMData;
    PRGROMSize = PRGROM.size()/16384;
    PRGROMLastBankPointer = (PRGROMSize - 2) * 16384;
    CHRRAM.reserve(8192);
}

uint8_t Mapper002::CPUread(uint16_t address) {
    if (address >= 0x8000 && address < 0xC000) {
        address -= 0x8000;
        address += PRGROMMapNumber * 16384;
        return PRGROM[address];
    }
    else {
        address = address - 0xC000 + PRGROMLastBankPointer;
        return PRGROM[address];
    }
    return 0;
}

void Mapper002::CPUwrite(uint16_t address, uint8_t data) {
    if (address >= 0x8000) {
        PRGROMMapNumber = data;
    }
    return;
}

uint8_t Mapper002::PPUread(uint16_t address) {
    if (address < 0x1000) {
        return CHRRAM[address];
    }
    return 0;
}

void Mapper002::PPUwrite(uint16_t address, uint8_t data) {
    // do nothing
}