/*
   Copyright [2021] [juwonpee]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

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