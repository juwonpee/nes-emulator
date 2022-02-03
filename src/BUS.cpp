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

#include "BUS.h"

using namespace std;

BUS::BUS(string _PRGROMdirectory, string _PRGRAMdirectory, graphics_t* graphics, input_t* input) {
	PRGROMdirectory = _PRGROMdirectory;
	PRGRAMdirectory = _PRGRAMdirectory;
	graphicsQueue = graphics;
	inputQueue = input;
	ram = new RAM();
	nesCart = new Cart(_PRGROMdirectory, _PRGRAMdirectory);
	nesCPU = new CPU(this);
	nesPPU = new PPU(this);
	// TODO: APU PPU classes here
}

BUS::~BUS() {
	delete graphicsQueue;
	delete inputQueue;

	delete nesCPU;
	delete nesCart;
	delete ram;
}

uint8_t BUS::CPUread(uint16_t _address) {
	address = _address;
	if (_address < 0x0800) {
		return ram -> read(_address);
	}
	else if (_address < 0x2000) {
		return ram -> read(_address & 0x0800);
		return CPUread(_address & 0x0800);
	}
	else if (_address < 0x2008) {
		nesPPU->read(_address);
	}
	else if (_address < 0x4000) {

	}
	else if (_address < 0x4018) {
		// APU & IO registers
	}
	else if (_address < 0x4020) {
		// NES test mode
	}
	else if (_address < 0xFFFF) {
		return nesCart -> CPUread(_address);
	}
	return 0;
}

void BUS::CPUwrite(uint16_t _address, uint8_t _data) {
	address = _address;
	data = _data;
	if (_address < 0x0800) {
		ram -> write(_address, _data);
	}
	else if (_address < 0x2000) {
		ram -> write(_address & 0x0800, _data);
	}
	else if (_address < 0x2008) {
		nesPPU->write(_address, _data);
	}
	else if (_address < 0x4000) {
		// TODO: Mirror of 0x2000~0x2007
		// repeats every 8 bytes
	}
	else if (_address < 0x4018) {
		// APU & IO registers
	}
	else if (_address < 0x4020) {
		// NES test mode
	}
	else if (_address < 0xFFFF) {
		nesCart -> CPUwrite(_address, _data);
	}
}

uint8_t BUS::PPUread(uint16_t address) {
	return nesCart->PPUread(address);
}

void BUS::PPUwrite(uint16_t address, uint8_t data) {
	nesCart->PPUwrite(address, data);
}

void BUS::clock(uint64_t _clocks) {
	if (_clocks == 0) {
		while(1) {
			clocks++;
			// Implement clock timing
			if (clocks % 12 == 0) {
				nesCPU->clock();
			}
			if (clocks % 5 == 0) {
				nesPPU->clock();
			}
		}
	}
	else {
		for (int __clocks = 0; __clocks < _clocks; __clocks++) {
			cout << "Executing clock: " << __clocks + 1 << " of " << _clocks << endl;
			nesCPU -> clock();
			clocks++;
			dumpCPU();
		}
		cout << "Total " << clocks << " executed" << endl;
	}
}

void BUS::dumpCPU() {
	CPUstatus temp = nesCPU -> dumpCPU();

	ofstream log;
	if (temp.instructionClocks == 0) {
		log.open("Debug log.txt", ios::out | ios::trunc);
		log << hex << setw(6) << left << temp.PC;
		log << setw(4) << left << temp.opcode;
		switch(temp.addressMode) {
			case acc:
				log << setw(4) << left << temp.opcode;
				break;
			case abl:
				log << setw(7) << left << temp.operandHigh << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.operandLow << temp.operandHigh;
				break;
			case abx:
				log << setw(7) << left << temp.operandHigh << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case aby:
				log << setw(7) << left << temp.operandHigh << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case imm:
				log << setw(7) << left << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << (uint8_t)temp.finalData;
				break;
			case imp:
				log << setw(7) << left << "";
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "";
				break;
			case ind:
				log << setw(7) << left << temp.operandHigh << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case xin:
				log << setw(7) << left << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case yin:
				log << setw(7) << left << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case rel:
				log << setw(7) << left << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case zpg:
				log << setw(7) << left << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case zpx:
				log << setw(7) << left << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case zpy:
				log << setw(7) << left << temp.operandLow;
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "$" << temp.finalAddress;
				break;
			case axx:
				log << setw(7) << left << "";
				log << setw(4) << left << temp.opcode;
				log << setw(7) << left << "";
				break;
		};

		log << setw(4) << left << "A:" << temp.A;
		log << setw(4) << left << "X:" << temp.X;
		log << setw(4) << left << "Y:" << temp.Y;
		log << setw(5) << left << "SP:" << temp.SP;
		log << setw(5) << left << "SR:" << temp.SR.byte << endl;
	}
	



	cout << "CPU registers" << endl;
	cout << "opcode : " << temp.opcode << endl;
	cout << "Instruction Mode : ";
	switch (temp.addressMode) {
		case acc:
			cout << "acc" << endl;
			break;
		case abl:
			cout << "abl" << endl;
			break;
		case abx:
			cout << "abx" << endl;
			break;
		case aby:
			cout << "aby" << endl;
			break;
		case imm:
			cout << "imm" << endl;
			break;
		case imp:
			cout << "imp" << endl;
			break;
		case ind:
			cout << "ind" << endl;
			break;
		case xin:
			cout << "xin" << endl;
			break;
		case yin:
			cout << "yin" << endl;
			break;
		case rel:
			cout << "Operands: " << temp.operandLow << endl;
			cout << "rel" << endl;
			break;
		case zpg:
			cout << "Operands: " << temp.operandLow << endl;
			cout << "zpg" << endl;
			break;
		case zpx:
			cout << "Operands: " << temp.operandLow << endl;
			cout << "zpx" << endl;
			break;
		case zpy:
			cout << "Operands: " << temp.operandLow << endl;
			cout << "zpy" << endl;
			break;
		case axx:
			cout << "Operands: " << temp.operandLow << endl;
			cout << "axx" << endl;
			break;
	}
	cout << "Instruction Clocks : " << hex << (uint16_t)temp.instructionClocks << endl;
	
	cout << "A   : " << hex << (uint16_t)temp.A << endl;
	cout << "X   : " << hex << (uint16_t)temp.X << endl;
	cout << "Y   : " << hex << (uint16_t)temp.Y << endl;
	cout << "SP  : " << hex << (uint16_t)temp.SP << endl;
	cout << "PC  : " << hex << temp.PC << endl;
	cout << "SR  : " << hex << (uint16_t)temp.SR.byte << endl;
	cout << "Status Registers" << endl;
	cout << "Carry     : " << hex << (uint16_t)temp.SR.C << endl;
	cout << "Zero      : " << hex << (uint16_t)temp.SR.Z << endl;
	cout << "Interrupt : " << hex << (uint16_t)temp.SR.I << endl;
	cout << "Decimal   : " << hex << (uint16_t)temp.SR.D << endl;
	cout << "Break     : " << hex << (uint16_t)temp.SR.B << endl;
	cout << "Ignore    : " << hex << (uint16_t)temp.SR.ignore << endl;
	cout << "Carry     : " << hex << (uint16_t)temp.SR.C << endl;
	cout << "Negative  : " << hex << (uint16_t)temp.SR.N << endl << endl;
}