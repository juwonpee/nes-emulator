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
#include "BUS.h"

using namespace std;

// Controller ($2000) > write
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
typedef struct PPUCTRL_t {
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

// Mask ($2001) > write
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
typedef struct PPUMASK_t {
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

// Status ($2002) < read
// 7  bit  0
// ---- ----
// VSO. ....
// |||| ||||
// |||+-++++- Least significant bits previously written into a PPU register
// |||        (due to register not being updated for this address)
// ||+------- Sprite overflow. The intent was for this flag to be set
// ||         whenever more than eight sprites appear on a scanline, but a
// ||         hardware bug causes the actual behavior to be more complicated
// ||         and generate false positives as well as false negatives; see
// ||         PPU sprite evaluation. This flag is set during sprite
// ||         evaluation and cleared at dot 1 (the second dot) of the
// ||         pre-render line.
// |+-------- Sprite 0 Hit.  Set when a nonzero pixel of sprite 0 overlaps
// |          a nonzero background pixel; cleared at dot 1 of the pre-render
// |          line.  Used for raster timing.
// +--------- Vertical blank has started (0: not in vblank; 1: in vblank).
//            Set at dot 1 of line 241 (the line *after* the post-render
//            line); cleared after reading $2002 and at dot 1 of the
//            pre-render line.
typedef struct PPUSTATUS_t {
	union {
		uint8_t data;
		struct {
			uint8_t lsb:5;
			uint8_t sprite_overflow:1;
			uint8_t sprite_hit:1;
			uint8_t vertical_blank:1;
		};
	};
} PPUSTATUS_t;

// OAM address ($2003) > write
// OAM address port
typedef uint8_t OAMADDR_t;

// OAM data ($2004) <> read/write
// OAM data port
typedef uint8_t OAMDATA_t;

// Scroll ($2005) >> write x2
// PPU scrolling position register
typedef uint8_t PPUSCROLL_t;

// Address ($2006) >> write x2
// PPU address register
typedef uint8_t PPUADDR_t;

// Data ($2007) <> read/write
// PPU data port
typedef uint8_t PPUDATA_t;

// OAM DMA ($4014) > write
// OAM DMA register (high byte)
typedef uint8_t OAMDMA_t;


// sprite
typedef struct sprite_t {
	pixel_colour_t pixel[8][8];
} sprite_t;

class BUS;


class PPU {
	public:
	PPU(BUS* b);
	~PPU();

	void clock();

	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);

	private:
		BUS* bus;

		// Registers
		PPUCTRL_t PPUCTRL;
		PPUMASK_t PPUMASK;
		PPUSTATUS_t PPUSTATUS;
		OAMADDR_t OAMADDR;
		OAMDATA_t OAMDATA;
		PPUSCROLL_t PPUSCROLL;
		PPUADDR_t PPUADDR;
		PPUDATA_t PPUDATA;
		OAMDMA_t OAMDMA;

		uint32_t startUpClock = 0;
		// 0: left (0x0000~0x0FFF), 1: right(0x1000~0x1FFF)
		sprite_t pattern_table[2][16][16];

	private: 
		// convenience registers
		bool address_latch;
		uint8_t data_buffer;
		uint16_t address_buffer;
	
		pixel_colour_t pixel_colour[0xFF];


		uint8_t PPUread(uint16_t address);
		void PPUwrite(uint16_t address, uint8_t data);
		uint8_t CPUread(uint16_t address);
		void CPUwrite(uint16_t address, uint8_t data);
		void getPatternTable(uint8_t pallete, uint8_t pixel);
		pixel_colour_t getColourFromPallete(uint8_t pallete, uint8_t pixel);
};

