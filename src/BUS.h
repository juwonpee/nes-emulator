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

#include <string>
#include <chrono>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "types.h"
#include "CPU.h"
#include "PPU.h"
#include "Cart.h"
#include "RAM.h"

using namespace std;

class CPU;
class PPU;
class Cart;
class RAM;

class BUS {
	public:
		BUS(string _PRGROMdirectory, string _PRGRAMdirectory, graphics_t* graphics, input_t* input);
		~BUS();


		uint8_t CPUread(uint16_t _address);
		void CPUwrite(uint16_t _address, uint8_t _data);
		uint8_t PPUread(uint16_t address);
		void PPUwrite(uint16_t address, uint8_t data);

		void write(pixel_colour_t _pixel);
		
		// debug functions
		uint64_t clocks = 0;
		void clock(uint64_t _clocks);
		void dumpCPU();

	private:
		graphics_t* graphicsQueue;
		input_t* inputQueue;


		uint16_t address;
		uint8_t data;


		string PRGROMdirectory;
		string PRGRAMdirectory;
		CPU* nesCPU;
		PPU* nesPPU;
		Cart* nesCart;
		RAM* ram;

		// Debug stuffs
		ofstream log;

		void runSingleClock();
};