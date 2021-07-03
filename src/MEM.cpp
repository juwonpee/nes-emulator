#include "types.h"
#include "MEM.h"

#define WRAM 0x0000
#define IO 0x2000
#define EXPANSION 0x5000
#define CRAM 0x6000
#define LCROM 0x8000
#define UCROM 0xc000

MEM::MEM() {

};

uint8_t MEM::read(uint16_t address) {
    if (WRAM <= address && address < IO) {
        // return from WRAM
        // TODO
    }
    else if (IO <= address && address < EXPANSION) {
        // do IO stuff
        // TODO
    }
    else if (EXPANSION <= address && address < CRAM) {
        // do expansion module stuff
        // TODO
    }
    else if (CRAM <= address && address < LCROM) {
        // return from cartridge ram
        // TODO
        return cRAM[address - CRAM];
    }
    else if (LCROM <= address && address < UCROM) {
        // return from cartridge rom
        // TODO
        return lcROM[address - LCROM];
    }
    else if (UCROM <= address && address < 0xFFFF) {
        // return from cartridge rom
        // TODO
        return ucROM[address - UCROM];
    }
    return 0;
}