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

#include "Mapper.h"



Mapper::Mapper(
    int mapperType, 
    uint8_t PRGROM, 
    uint8_t CHRROM, 
    mirrorType _mirror,
    screenType _screen,
    vector<uint8_t> trainerData, 
    vector<uint8_t> PRGROMData, 
    vector<uint8_t> CHRROMData
)
{
    mapper = mapperType;
    switch (mapperType) {                           
        case 0:
            mapper000 = new Mapper000(_mirror, PRGROMData);
            break;
        case 2:
            mapper002 = new Mapper002(_mirror, PRGROMData);
            break;
        case 94:
            mapper094 = new Mapper094(_mirror, PRGROMData);
            break;
        case 180:
            mapper180 = new Mapper180(_mirror, PRGROMData);
            break;
        
    }
}

Mapper::~Mapper() {
}

uint8_t Mapper::CPUread(uint16_t address) {
    switch (mapper) {
        case 0:
            return mapper000 -> CPUread(address);
        case 2:
            return mapper002 -> CPUread(address);
        case 94:
            return mapper094 -> CPUread(address);
        case 180:
            return mapper180 -> CPUread(address);
    }
    return 0;
}
void Mapper::CPUwrite(uint16_t address, uint8_t data) {
    switch (mapper) {
        case 0:
            mapper000 -> CPUwrite(address, data);
        case 2:
            mapper002 -> CPUwrite(address, data);
        case 94:
            mapper094 -> CPUwrite(address, data);
        case 180:
            mapper180 -> CPUwrite(address, data);
    }
}
uint8_t Mapper::PPUread(uint16_t address) {
    switch (mapper) {
        case 0:
            return mapper000 -> PPUread(address);
        case 2:
            return mapper002 -> PPUread(address);
        case 94:
            return mapper094 -> PPUread(address);
        case 180:
            return mapper180 -> PPUread(address);
    }
    return 0;
}
void Mapper::PPUwrite(uint16_t address, uint8_t data) {
    switch (mapper) {
        case 0:
            mapper000 -> PPUwrite(address, data);
        case 2:
            mapper002 -> PPUwrite(address, data);
        case 94:
            mapper094 -> PPUwrite(address, data);
        case 180:
            mapper180 -> PPUwrite(address, data);
    }
}