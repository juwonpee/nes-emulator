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
#include <vector>
#include "Mapper000.h"
#include "Mapper002.h"
#include "Mapper094.h"
#include "Mapper180.h"


using namespace std;

class Mapper {
    public:
        Mapper(
            int mapperType, 
            uint8_t PRGROM, 
            uint8_t CHRROM, 
            mirrorType _mirror,
            screenType _screen,
            vector<uint8_t> trainerData, 
            vector<uint8_t> PRGROMData, 
            vector<uint8_t> CHRROMData
        );
        ~Mapper();

        uint8_t CPUread(uint16_t address);
        void CPUwrite(uint16_t address, uint8_t write);
        uint8_t PPUread(uint16_t address);
        void PPUwrite(uint16_t address, uint8_t write);
    private:
        int mapper;
        Mapper000* mapper000;
        Mapper002* mapper002;
        Mapper094* mapper094;
        Mapper180* mapper180;
        
};