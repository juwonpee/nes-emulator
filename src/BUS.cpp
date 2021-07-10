#include "BUS.h"

using namespace std;

BUS::BUS(string _PRGROMdirectory, string _PRGRAMdirectory, graphics_t* graphics, input_t* input) {
    PRGROMdirectory = _PRGROMdirectory;
    PRGRAMdirectory = _PRGRAMdirectory;
    graphicsQueue = graphics;
    inputQueue = input;
    ram = new RAM();
    nesCartridge = new Cart(_PRGROMdirectory, _PRGRAMdirectory);
    nesCPU = new CPU(this);
    // TODO: APU PPU classes here
}

BUS::~BUS() {
    delete graphicsQueue;
    delete inputQueue;

    delete nesCPU;
    delete nesCartridge;
    delete ram;
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

void BUS::clock(uint64_t _clocks) {
    if (_clocks == 0) {
        while(1) {
            clocks++;
            // Implement clock timing
            nesCPU -> clock();
        }
    }
    else {
        for (int __clocks = 0; __clocks < _clocks; __clocks++) {
            cout << "Executing clock: " << __clocks + 1 << " of " << _clocks << endl;
            nesCPU -> clock();
            clocks++;
            dumpCPU();
        }
        cout << "Total " << clocks << " executed" << endl;
    }
}

void BUS::dumpCPU() {
    cout << "CPU registers" << endl;
    CPUstatus temp = nesCPU -> dumpCPU();
    cout << "opcode : " << temp.opcode << endl;
    cout << "A   : " << hex << temp.A << endl;
    cout << "X   : " << hex << temp.X << endl;
    cout << "Y   : " << hex << temp.Y << endl;
    cout << "SP  : " << hex << temp.SP << endl;
    cout << "PC  : " << hex << temp.PC << endl;
    cout << "SR  : " << hex << temp.SR.byte << endl;
    cout << "Carry     : " << temp.SR.C << endl;
    cout << "Zero      : " << temp.SR.Z << endl;
    cout << "Interrupt : " << temp.SR.I << endl;
    cout << "Decimal   : " << temp.SR.D << endl;
    cout << "Break     : " << temp.SR.B << endl;
    cout << "Ignore    : " << temp.SR.ignore << endl;
    cout << "Carry     : " << temp.SR.C << endl;
    cout << "Negative  : " << temp.SR.N << endl << endl;
}