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

#include <iostream>
#include <stdlib.h>
#include <algorithm>

#include "Cart.h"

using namespace std;

Cart::Cart(string PRGROMdirectory, string PRGRAMdirectory) {
    
    iNES.open(PRGROMdirectory, ios::binary);
    if (iNES.fail()) {
        cout << "File does not exist" << endl;
        exit(EXIT_FAILURE);
    }
    if (PRGRAMdirectory == "") {
        // TODO: implement PRGRAM, Battery backed up cartridge RAM
    }


    buffer = new vector<uint8_t>(istreambuf_iterator<char>(iNES), {});
    
    
    // Check whether iNES file format is valid
    if ((*buffer)[0] == 'N' & (*buffer)[1] == 'E' & (*buffer)[2] == 'S' & (*buffer)[3] == 0x1A) {
        // Check header
        PRGROM = (*buffer)[4];
        CHRROM = (*buffer)[5];
        FLAGS6.input = (*buffer)[6];
        FLAGS7.input = (*buffer)[7];
        FLAGS8.input = MAPPER.input = (*buffer)[8];
        FLAGS9.input = ROMSIZE.input = (*buffer)[9];
        FLAGS10.input = EEPROMSIZE.input = (*buffer)[10];
        RAMSIZE.input = (*buffer)[11];
        TIMING.input = (*buffer)[12];
        TYPE.input = (*buffer)[13];

    }
    else {
        cout << "Invalid cartridge format" << endl;
        exit(EXIT_FAILURE);
    }

    // Copy data from buffer into mappers
    long bufferPointer = 16;
    if (FLAGS6.T) {
        copy(&(*buffer)[bufferPointer], &(*buffer)[bufferPointer + 512], back_inserter(trainer));
        bufferPointer += 512;
    }
    copy(&(*buffer)[bufferPointer], &(*buffer)[bufferPointer + PRGROM * 16384], back_inserter(bufferPRGROM));
    bufferPointer += PRGROM * 16384;
    copy(&(*buffer)[bufferPointer], &(*buffer)[bufferPointer + CHRROM * 8192], back_inserter(bufferCHRROM));
    

    if (FLAGS7.iNES2 == 0b10) iNES2();
    else iNES1();


}

uint8_t Cart::CPUread(uint16_t address) {
    return mapper -> CPUread(address);
}

void Cart::CPUwrite(uint16_t address, uint8_t data) {
    mapper -> CPUwrite(address, data);
}

uint8_t Cart::PPUread(uint16_t address) {
    return mapper -> PPUread(address);
}

void Cart::PPUwrite(uint16_t address, uint8_t data) {
    mapper -> PPUwrite(address, data);
}

Cart::~Cart() {
    delete buffer;
    delete mapper;
}
 
void Cart::iNES1() {
    cout << "ROM header format: iNES1.0" << endl;
    int mapperNumber = FLAGS6.N + (FLAGS7.N << 4);
    cout << "Mapper number: " << mapperNumber << endl;
    cout << "Program ROM Size: " << (int)PRGROM * 16384 << endl;
    cout << "Character ROM Size: " << (int) CHRROM * 8192 << endl;
    mapper = new Mapper(mapperNumber, PRGROM, CHRROM, static_cast<mirrorType>(FLAGS6.M), static_cast<screenType>(FLAGS6.F), trainer, bufferPRGROM, bufferCHRROM);
}

void Cart::iNES2() {
    cout << "ROM header format: iNES2.0" << endl;
}