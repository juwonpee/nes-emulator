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

#include "PPU.h"

using namespace std;

PPU::PPU(BUS* b) {
	bus = b;

	// Init registers 
	PPUCTRL.data = 0;
	PPUMASK.data = 0;
	PPUSTATUS.data = 0;
	OAMADDR = 0;
	OAMDATA = 0;
	PPUSCROLL = 0;
	PPUADDR = 0;
	PPUDATA = 0;
	OAMDATA = 0;

	// Init pixel colour values
	pixel_colour[0x00].r = 84;  pixel_colour[0x00].g = 84;  pixel_colour[0x00].b = 84;
	pixel_colour[0x01].r = 0;   pixel_colour[0x01].g = 3;   pixel_colour[0x01].b = 116;
	pixel_colour[0x02].r = 8;   pixel_colour[0x02].g = 16;  pixel_colour[0x02].b = 144;
	pixel_colour[0x03].r = 48;  pixel_colour[0x03].g = 0;   pixel_colour[0x03].b = 136;
	pixel_colour[0x04].r = 68;  pixel_colour[0x04].g = 0;   pixel_colour[0x04].b = 100;
	pixel_colour[0x05].r = 92;  pixel_colour[0x05].g = 0;   pixel_colour[0x05].b = 48;
	pixel_colour[0x06].r = 84;  pixel_colour[0x06].g = 4;   pixel_colour[0x06].b = 0;
	pixel_colour[0x07].r = 60;  pixel_colour[0x07].g = 24;  pixel_colour[0x07].b = 0;
	pixel_colour[0x08].r = 32;  pixel_colour[0x08].g = 42;  pixel_colour[0x08].b = 0;
	pixel_colour[0x09].r = 8;   pixel_colour[0x09].g = 58;  pixel_colour[0x09].b = 0;
	pixel_colour[0x0A].r = 0;   pixel_colour[0x0A].g = 64;  pixel_colour[0x0A].b = 0;
	pixel_colour[0x0B].r = 0;   pixel_colour[0x0B].g = 60;  pixel_colour[0x0B].b = 0;
	pixel_colour[0x0C].r = 0;   pixel_colour[0x0C].g = 50;  pixel_colour[0x0C].b = 60;
	pixel_colour[0x0D].r = 0;   pixel_colour[0x0D].g = 0;   pixel_colour[0x0D].b = 0;
	pixel_colour[0x0E].r = 0;   pixel_colour[0x0E].g = 0;   pixel_colour[0x0E].b = 0;
	pixel_colour[0x0F].r = 0;   pixel_colour[0x0F].g = 0;   pixel_colour[0x0F].b = 0;

	pixel_colour[0x10].r = 152; pixel_colour[0x10].g = 150; pixel_colour[0x10].b = 152;
	pixel_colour[0x11].r = 8;   pixel_colour[0x11].g = 76;  pixel_colour[0x11].b = 196;
	pixel_colour[0x12].r = 48;  pixel_colour[0x12].g = 50;  pixel_colour[0x12].b = 236;
	pixel_colour[0x13].r = 92;  pixel_colour[0x13].g = 30;  pixel_colour[0x13].b = 228;
	pixel_colour[0x14].r = 136; pixel_colour[0x14].g = 20;  pixel_colour[0x14].b = 176;
	pixel_colour[0x15].r = 160; pixel_colour[0x15].g = 20;  pixel_colour[0x15].b = 100;
	pixel_colour[0x16].r = 152; pixel_colour[0x16].g = 34;  pixel_colour[0x16].b = 32;
	pixel_colour[0x17].r = 120; pixel_colour[0x17].g = 60;  pixel_colour[0x17].b = 0;
	pixel_colour[0x18].r = 84;  pixel_colour[0x18].g = 90;  pixel_colour[0x18].b = 0;
	pixel_colour[0x19].r = 40;  pixel_colour[0x19].g = 114; pixel_colour[0x19].b = 0;
	pixel_colour[0x1A].r = 8;   pixel_colour[0x1A].g = 124; pixel_colour[0x1A].b = 0;
	pixel_colour[0x1B].r = 0;   pixel_colour[0x1B].g = 118; pixel_colour[0x1B].b = 40;
	pixel_colour[0x1C].r = 0;   pixel_colour[0x1C].g = 102; pixel_colour[0x1C].b = 120;
	pixel_colour[0x1D].r = 0;   pixel_colour[0x1D].g = 0;   pixel_colour[0x1D].b = 0;
	pixel_colour[0x1E].r = 0;   pixel_colour[0x1E].g = 0;   pixel_colour[0x1E].b = 0;
	pixel_colour[0x1F].r = 0;   pixel_colour[0x1F].g = 0;   pixel_colour[0x1F].b = 0;

	pixel_colour[0x20].r = 236;	pixel_colour[0x20].g = 238;	pixel_colour[0x20].b = 236;
	pixel_colour[0x21].r = 76;	pixel_colour[0x21].g = 154;	pixel_colour[0x21].b = 236;
	pixel_colour[0x22].r = 120;	pixel_colour[0x22].g = 124;	pixel_colour[0x22].b = 236;
	pixel_colour[0x23].r = 176;	pixel_colour[0x23].g = 98;	pixel_colour[0x23].b = 236;
	pixel_colour[0x24].r = 228;	pixel_colour[0x24].g = 84;	pixel_colour[0x24].b = 236;
	pixel_colour[0x25].r = 236;	pixel_colour[0x25].g = 88;	pixel_colour[0x25].b = 180;
	pixel_colour[0x26].r = 236;	pixel_colour[0x26].g = 106;	pixel_colour[0x26].b = 100;
	pixel_colour[0x27].r = 212;	pixel_colour[0x27].g = 136;	pixel_colour[0x27].b = 32;
	pixel_colour[0x28].r = 160;	pixel_colour[0x28].g = 170;	pixel_colour[0x28].b = 0;
	pixel_colour[0x29].r = 116;	pixel_colour[0x29].g = 196;	pixel_colour[0x29].b = 0;
	pixel_colour[0x2A].r = 76;	pixel_colour[0x2A].g = 208;	pixel_colour[0x2A].b = 32;
	pixel_colour[0x2B].r = 56;	pixel_colour[0x2B].g = 204;	pixel_colour[0x2B].b = 108;
	pixel_colour[0x2C].r = 56;	pixel_colour[0x2C].g = 180;	pixel_colour[0x2C].b = 204;
	pixel_colour[0x2D].r = 60;	pixel_colour[0x2D].g = 60;	pixel_colour[0x2D].b = 60;
	pixel_colour[0x2E].r = 0;	pixel_colour[0x2E].g = 0;	pixel_colour[0x2E].b = 0;
	pixel_colour[0x2F].r = 0;	pixel_colour[0x2F].g = 0;	pixel_colour[0x2F].b = 0;

	pixel_colour[0x30].r = 236;	pixel_colour[0x30].g = 238;	pixel_colour[0x30].b = 236;
	pixel_colour[0x31].r = 168;	pixel_colour[0x31].g = 204;	pixel_colour[0x31].b = 236;
	pixel_colour[0x32].r = 188;	pixel_colour[0x32].g = 188;	pixel_colour[0x32].b = 236;
	pixel_colour[0x33].r = 212;	pixel_colour[0x33].g = 178;	pixel_colour[0x33].b = 236;
	pixel_colour[0x34].r = 236;	pixel_colour[0x34].g = 174;	pixel_colour[0x34].b = 236;
	pixel_colour[0x35].r = 236;	pixel_colour[0x35].g = 174;	pixel_colour[0x35].b = 212;
	pixel_colour[0x36].r = 236;	pixel_colour[0x36].g = 180;	pixel_colour[0x36].b = 176;
	pixel_colour[0x37].r = 228;	pixel_colour[0x37].g = 196;	pixel_colour[0x37].b = 144;
	pixel_colour[0x38].r = 204;	pixel_colour[0x38].g = 210;	pixel_colour[0x38].b = 120;
	pixel_colour[0x39].r = 180;	pixel_colour[0x39].g = 222;	pixel_colour[0x39].b = 120;
	pixel_colour[0x3A].r = 168;	pixel_colour[0x3A].g = 226;	pixel_colour[0x3A].b = 144;
	pixel_colour[0x3B].r = 152;	pixel_colour[0x3B].g = 226;	pixel_colour[0x3B].b = 180;
	pixel_colour[0x3C].r = 160;	pixel_colour[0x3C].g = 214;	pixel_colour[0x3C].b = 228;
	pixel_colour[0x3D].r = 160;	pixel_colour[0x3D].g = 162;	pixel_colour[0x3D].b = 160;
	pixel_colour[0x3E].r = 0;	pixel_colour[0x3E].g = 0;	pixel_colour[0x3E].b = 0;
	pixel_colour[0x3F].r = 0;	pixel_colour[0x3F].g = 0;	pixel_colour[0x3F].b = 0;
}

PPU::~PPU() {

}

void PPU::clock() {
	if (startUpClock < 29658) {
		startUpClock++;
	}
	else {

	}
}

uint8_t PPU::read(uint16_t address) {
	uint8_t returnInt;
	switch (address) {
		case 0x2002:
			address_latch = 0;
			// Clear bit 7
			returnInt = PPUSTATUS.data;
			PPUSTATUS.data &= 0x8F;

			return returnInt;
		case 0x2004:
			return OAMDATA;
		case 0x2007:
			PPUDATA = PPUread(address_buffer);
			return PPUDATA;
		default:
			return 0;
	};
}

void PPU::write(uint16_t address, uint8_t data) {
	switch (address) {
		case 0x2000:
			PPUCTRL.data = data;
			break;
		case 0x2001:
			PPUMASK.data = data;
			break;
		case 0x2003:
			OAMADDR = data;
			break;
		case 0x2004:
			OAMDATA = data;
			break;
		case 0x2005:
			if (!scroll_buffer) {
				scroll_buffer = (scroll_buffer & 0xFF00) + data;
				scroll_latch = true;
			}
			else {
				scroll_buffer = (scroll_buffer & 0x00FF) + data;
				scroll_latch = false;
			}
			PPUSCROLL = data;
			break;
		case 0x2006:
			if (!address_latch) {
				address_buffer = (address_buffer & 0xFF00) | data;
				address_latch = true;
			}
			else {
				address_buffer = (address_buffer & 0x00FF) | (data << 8);
				address_latch = false;
			}
			PPUADDR = data;
			break;
		case 0x2007:
			PPUDATA = data;
			PPUwrite(address_buffer, data);
			break;
		case 0x4014:
			OAMDMA = data;
			break;
	};
}

uint8_t PPU::PPUread(uint16_t address) {
	return bus->PPUread(address);
}

void PPU::PPUwrite(uint16_t address, uint8_t data) {
	bus->PPUwrite(address, data);
}

uint8_t PPU::CPUread(uint16_t address) {
	return bus->CPUread(address);
}

void PPU::CPUwrite(uint16_t address, uint8_t data) {
	bus->CPUwrite(address, data);
}

void PPU::getPatternTable(uint8_t pallete, uint8_t pixel) {
	for (int p = 0; p < 2; p++) {	// Pattern table
		for (int x = 0; x < 16; x++) {	// Tile X offset
			for (int y = 0; y < 16; y++) {	// Tile Y offset
				for (int i = 0; i < 8; i++) {	// Tile pixel x offset
					for (int j = 0; j < 8; i++) {	// Tile pixel y offset
						uint16_t offset = 0;
						offset += x * 16 + y * 256 + j;
						uint8_t pixel = (offset >> i) & 0x1;
						pixel += ((offset + 8) >> i) &0x1;
						pattern_table[p][x][y].pixel[i][j] = getColourFromPallete(pallete, pixel);
					}
				}
			}
		}
	}
}

pixel_colour_t PPU::getColourFromPallete(uint8_t pallete, uint8_t pixel) {
	return pixel_colour[PPUread(0x3F00 + (pallete << 2) + pixel) * 0x3F];
}