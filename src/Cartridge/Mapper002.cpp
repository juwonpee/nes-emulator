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

#include "types.h"
#include "Mapper002.h"

using namespace std;

Mapper002:: Mapper002(
    mirrorType _mirror,
    vector<uint8_t> PRGROMData
)
{
    cout << "Mapper002 init" << endl;
    mirror = _mirror;
    PRGROM = PRGROMData;
    PRGROMSize = PRGROM.size()/16384;
    PRGROMLastBankPointer = (PRGROMSize - 1) * 16384;
    CHRRAM.reserve(8192);
}

uint8_t Mapper002::CPUread(uint16_t address) {
    if (address >= 0x8000 && address < 0xC000) {
        uint32_t temp = address;
        temp -= 0x8000;
        temp += PRGROMMapNumber * 16384;
        return PRGROM[temp];
    }
    else {
        uint32_t temp = address;
        temp -= 0xC000;
        temp += PRGROMLastBankPointer;
        return PRGROM[temp];
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