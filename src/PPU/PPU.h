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

using namespace std;


// VPHB SINN
// |||| ||||
// |||| ||++- Base nametable address
// |||| ||    (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
// |||| |+--- VRAM address increment per CPU read/write of PPUDATA
// |||| |     (0: add 1, going across; 1: add 32, going down)
// |||| +---- Sprite pattern table address for 8x8 sprites
// ||||       (0: $0000; 1: $1000; ignored in 8x16 mode)
// |||+------ Background pattern table address (0: $0000; 1: $1000)
// ||+------- Sprite size (0: 8x8 pixels; 1: 8x16 pixels)
// |+-------- PPU master/slave select
// |          (0: read backdrop from EXT pins; 1: output color on EXT pins)
// +--------- Generate an NMI at the start of the
//            vertical blanking interval (0: off; 1: on)
typedef struct uint8_t PPUCTRL_t {
    union {
        uint8_t data;
        struct {
            uint8_t base_nametable_address:2;
            uint8_t VRAM_address_increment:1;
            uint8_t sprite_pattern_table:1;
            uint8_t background_pattern_table;
            uint8_t sprite_size;
            uint8_t PPU_master_slave;
            uint8_t NMI_generate_time;
        };
    };
} PPUCTRL_t;

// 7  bit  0
// ---- ----
// BGRs bMmG
// |||| ||||
// |||| |||+- Greyscale (0: normal color, 1: produce a greyscale display)
// |||| ||+-- 1: Show background in leftmost 8 pixels of screen, 0: Hide
// |||| |+--- 1: Show sprites in leftmost 8 pixels of screen, 0: Hide
// |||| +---- 1: Show background
// |||+------ 1: Show sprites
// ||+------- Emphasize red (green on PAL/Dendy)
// |+-------- Emphasize green (red on PAL/Dendy)
// +--------- Emphasize blue

typedef struct uint8_t PPUMASK_t {
    union {
        uint8_t data;
        struct {
            uint8_t greyscale:1;
            uint8_t show_background_leftmost:1;
            uint8_t show_sprites_leftmost:1;
            uint8_t show_background:1;
            uint8_t show_sprites:1;
            uint8_t emphasize_red:1;
            uint8_t emphasize_green:1;
            uint8_t emphasize_blue:1;
        };
    };
} PPUMASK_t;



class PPU {
    public:
    PPU();
    ~PPU();

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    private:
        // Registers
        struct 
}

