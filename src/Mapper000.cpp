#include <iostream>

#include <Mapper000.h>


using namespace std;

Mapper000::Mapper000(
    mirrorType _mirror,
    vector<uint8_t> PRGROMData
)
{
    cout << "Mapper000 init" << endl;
    mirror = _mirror;
    PRGROM = PRGROMData;
    PRGROMSize = PRGROM.size()/16384;
    CHRRAM.reserve(8192);
}

Mapper000::~Mapper000() {

}

// CPU $6000-$7FFF: Family Basic only: PRG RAM, mirrored as necessary to fill entire 8 KiB window, write protectable with an external switch
// CPU $8000-$BFFF: First 16 KB of ROM.
// CPU $C000-$FFFF: Last 16 KB of ROM (NROM-256) or mirror of $8000-$BFFF (NROM-128).
uint8_t Mapper000::CPUread(uint16_t address) {
    if (address >= 0x8000 && address < 0xC000) {
        return PRGROM[address - 0x8000];
    }
    else {
        if (PRGROMSize == 2) return PRGROM[address - 0x8000];
        else return PRGROM[address - 0xC000];
    }
    return 0;
}

void Mapper000::CPUwrite(uint16_t address, uint8_t data) {
    // do nothing
}

uint8_t Mapper000::PPUread(uint16_t address) {
    if (address < 0x1000) {
        return CHRRAM[address];
    }
    return 0;
}

void Mapper000::PPUwrite(uint16_t address, uint8_t data) {
    // do nothing
}