#include "BUS.h"

BUS::BUS(std::string _directory, graphics* _graphics, input* _input) {
    directory = _directory;
    graphicsQueue = _graphics;
    inputQueue = _input;
    nesCPU = new CPU();
    nesCartridge = new Cart(_directory);
    // TODO: various other classes here
}

BUS::~BUS() {
    delete nesCPU;
    delete nesCartridge;
}

uint8_t BUS::read(uint16_t _address) {
    address = _address;
    if (_address < 0x0800) {
        // TODO: 2KB of work RAM
    }
    else if (_address < 0x1000) {
        // TODO: Mirror of 0x000~0x07FF
    }
    else if (_address < 0x1800) {
        // TODO: Mirror of 0x000~0x07FF
    }
    else if (_address < 0x2000) {
        // TODO: Mirror of 0x000~0x07FF
    }
    else if (_address < 0x2008) {
        // TODO: PPU control registers
    }
    else if (_address < 0x4000) {
        // TODO: Mirror of 0x2000~0x2007
        // Mirrored 1023 times, not including 0x2000~0x2007
    }
    else if (_address < 0x4020) {
        // TODO: Registers (Mostly APU)
    }
    else if (_address < 0x6000) {
        // TODO: Cartridge expansion rom
    }
    else if (_address < 0x8000) {
        // TODO: SRAM
    }
    else if (_address < 0xC000) {
        // TODO: PRG-ROM
    }
    else if (_address < 0x4000) {
        // TODO: more PRG-ROM
    }
    return 0;
}

void BUS::write(uint16_t _address, uint8_t _data) {
    address = _address;
    data = _data;
    if (_address < 0x0800) {
        // TODO: 2KB of work RAM
    }
    else if (_address < 0x1000) {
        // TODO: Mirror of 0x000~0x07FF
    }
    else if (_address < 0x1800) {
        // TODO: Mirror of 0x000~0x07FF
    }
    else if (_address < 0x2000) {
        // TODO: Mirror of 0x000~0x07FF
    }
    else if (_address < 0x2008) {
        // TODO: PPU control registers
    }
    else if (_address < 0x4000) {
        // TODO: Mirror of 0x2000~0x2007
        // Mirrored 1023 times, not including 0x2000~0x2007
    }
    else if (_address < 0x4020) {
        // TODO: Registers (Mostly APU)
    }
    else if (_address < 0x6000) {
        // TODO: Cartridge expansion rom
    }
    else if (_address < 0x8000) {
        // TODO: SRAM
    }
    else if (_address < 0xC000) {
        // TODO: PRG-ROM
    }
    else if (_address < 0x4000) {
        // TODO: more PRG-ROM
    }
}

void BUS::clock() {
    nesCPU -> clock();
    // TODO: lots of other classes
}