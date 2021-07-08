#include "BUS.h"

using namespace std;

BUS::BUS(string _PRGROMdirectory, string _PRGRAMdirectory, graphics* _graphics, input* _input) {
    PRGROMdirectory = _PRGROMdirectory;
    PRGRAMdirectory = _PRGRAMdirectory;
    graphicsQueue = _graphics;
    inputQueue = _input;
    ram = new RAM();
    nesCPU = new CPU();
    nesCartridge = new Cart(_PRGROMdirectory, _PRGRAMdirectory);
    // TODO: various other classes here
}

BUS::~BUS() {
    delete nesCPU;
    delete nesCartridge;
}

uint8_t BUS::CPUread(uint16_t _address) {
    address = _address;
    if (_address < 0x0800) {
        return ram -> read(_address);
    }
    else if (_address < 0x2000) {
        return ram -> read(_address & 0x0800);
        return CPUread(_address & 0x0800);
    }
    else if (_address < 0x2008) {
        // TODO: PPU control registers
    }
    else if (_address < 0x4000) {

    }
    else if (_address < 0x4018) {
        // APU & IO registers
    }
    else if (_address < 0x4020) {
        // NES test mode
    }
    else if (_address < 0xFFFF) {
        return nesCartridge -> CPUread(_address);
    }
    return 0;
}

void BUS::CPUwrite(uint16_t _address, uint8_t _data) {
    address = _address;
    data = _data;
    if (_address < 0x0800) {
        ram -> write(_address, _data);
    }
    else if (_address < 0x2000) {
        ram -> write(_address & 0x0800, _data);
    }
    else if (_address < 0x2008) {
        // TODO: PPU control registers
    }
    else if (_address < 0x4000) {
        // TODO: Mirror of 0x2000~0x2007
        // repeats every 8 bytes
    }
    else if (_address < 0x4018) {
        // APU & IO registers
    }
    else if (_address < 0x4020) {
        // NES test mode
    }
    else if (_address < 0xFFFF) {
        nesCartridge -> CPUwrite(_address, _data);
    }
}

void BUS::clock() {
    while (1) {
        nesCPU -> clock();
    // TODO: PPU, APU

    }
}