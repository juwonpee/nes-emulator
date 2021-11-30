#include "types.h"

// --------------------------------------- $10000
//  Upper Bank of Cartridge ROM
// --------------------------------------- $C000
//  Lower Bank of Cartridge ROM
// --------------------------------------- $8000
//  Cartridge RAM (may be battery-backed)
// --------------------------------------- $6000
//  Expansion Modules
// --------------------------------------- $5000
//  Input/Output
// --------------------------------------- $2000
//  2kB Internal RAM, mirrored 4 times
// --------------------------------------- $0000

class MEM {
    public:
        MEM();
        ~MEM();
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t data);
    private:
        // Work ram 4 banks
        uint8_t wRAM0[2048];
        uint8_t wRAM1[2048];
        uint8_t wRAM2[2048];
        uint8_t wRAM3[2048];
        // IO memory
        void* IOModule;
        uint8_t IO[12288];
        // Expansion modules
        uint8_t Expansion[4098];
        // Cartridge RAM
        // TODO
        void* cModule;
        uint8_t cRAM[2048];
        // Cartridge ROM
        uint8_t lcROM[16384];
        uint8_t ucROM[16384];
};