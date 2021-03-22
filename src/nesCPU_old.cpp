// #include "nesCPU.h"
// #include "Bus.h"

// // constructor
// nesCPU::nesCPU() {
//     using a = nesCPU;
//     opcodeLookup = {
//         { "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
// 		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
// 		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
// 		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
// 		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
// 		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
// 		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
// 		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
// 		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
// 		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
// 		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
// 		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
// 		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
// 		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
// 		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
// 		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
//     };
// }

// // deconstructor
// nesCPU::~nesCPU() {

// }



// //-------------------------------------------------------------------------------------------------
// // Connection to the bus

// uint8_t nesCPU::read(uint16_t addr) {
// 	return bus -> read(addr, false);
// }
// void nesCPU::write(uint16_t addr, uint8_t data) {
// 	bus -> write(addr, data);
// }

// //-------------------------------------------------------------------------------------------------
// // external inputs
// void nesCPU::reset() {
// 	addrAbs = 0xFFFC;
// 	uint16_t lo = read(addrAbs + 0);
// 	uint16_t hi = read(addrAbs + 1);

// 	// Set it
// 	pc = (hi << 8) | lo;

// 	// Reset internal registers
// 	a = 0;
// 	x = 0;
// 	y = 0;
// 	st = 0xFD;
// 	status = 0x00 | u;

// 	// Clear internal helper variables
// 	addrRel = 0x0000;
// 	addrAbs = 0x0000;
// 	fetched = 0x00;

// 	// Reset takes time
// 	cycles = 8;
// }

// void nesCPU::irq() {
// 	if (getFlag(i) == 0) {
// 		// write pc to stack, requires 2 writes as it is 16 bit wide
// 		write(0x0100 + st, (pc >> 8) & 0x00FF);
// 		st--;
// 		write(0x0100 + st, pc & 0x00FF);
// 		st--;

// 		// push status register to stack
// 		setFlag(b, 0);
// 		setFlag(u, 1);
// 		setFlag(i, 1);
// 		write(0x0100 + st, status);
// 		st--;

// 		// read PC from 0xFFFE
// 		addrAbs = 0xFFFE;
// 		uint16_t lo = read(addrAbs + 0);
// 		uint16_t hi = read(addrAbs + 1);
// 		pc = (hi << 8) | lo;

// 		//irq clocks
// 		cycles = 7;
// 	}
// }

// void nesCPU::nmi() {
// 	write(0x0100 + st, (pc >> 8) & 0x00FF);
// 	st--;
// 	write(0x0100 + st, pc & 0x00FF);
// 	st--;

// 	setFlag(b, 0);
// 	setFlag(u, 1);
// 	setFlag(i, 1);
// 	write(0x0100 + st, status);
// 	st--;

// 	addrAbs = 0xFFFA;
// 	uint16_t lo = read(addrAbs + 0);
// 	uint16_t hi = read(addrAbs + 1);
// 	pc = (hi << 8) | lo;

// 	cycles = 8;
// }

// void nesCPU::clock() {
// 	if (cycles == 0) {
// 		opcode = read(pc);					// get next instruction
// 		pc++;								
// 		cycles = opcodeLookup[opcode].cycles;
// 		setFlag(u, true);
// 		uint8_t operand1 = (this->*opcodeLookup[opcode].addrMode)();
// 		uint8_t operand2 = (this->*opcodeLookup[opcode].operate)();
// 	}
// 	cycles--;
// }

// bool nesCPU::complete() {
// 	if (cycles == 0) {
// 		return true;
// 	}
// 	else {
// 		return false;
// 	}
// }

// uint8_t nesCPU::getFlag(flags f) {
// 	return ((status & f) ? 1 : 0);
// }

// void nesCPU::setFlag(flags f, bool b) {
// 	if (b) {
// 		status |= f;
// 	}
// 	else {
// 		status &= -f;
// 	}
// }

// uint8_t nesCPU::fetch() {
// 	if (!(opcodeLookup[opcode].addrMode == &nesCPU::IMP))
// 		fetched = read(addrAbs);
// 	return fetched;
// }


// //-------------------------------------------------------------------------------------------------
// // Addressing modes
// //-------------------------------------------------------------------------------------------------

// uint8_t nesCPU::IMP() {
// 	fetched = a;
// 	return 0;
// }

// uint8_t nesCPU::IMM() {
// 	addrAbs = pc++;
// 	return 0;
// }

// uint8_t nesCPU::ZP0() {
// 	addrAbs = read(pc);
// 	pc++;
// 	addrAbs &= 0x00FF;
// 	return 0;
// }

// uint8_t nesCPU::ZPX() {
// 	addrAbs = read(pc) + x;
// 	pc++;
// 	addrAbs &= 0x00FF;
// 	return 0;
// }

// uint8_t nesCPU::ZPY() {
// 	addrAbs = read(pc) + y;
// 	pc++;
// 	addrAbs &= 0x00FF;
// 	return 0;
// }

// uint8_t nesCPU::REL() {
// 	addrRel = read(pc);
// 	pc++;
// 	if (addrRel & 0x80) {
// 		addrRel |= 0xFF00;
// 	}
// 	return 0;
// }

// uint8_t nesCPU::ABS() {
// 	uint8_t lo = read(pc);
// 	pc++;
// 	uint8_t hi = read(pc);
// 	pc++;
// 	addrAbs = (hi << 8) | lo;
// 	return 0;
// }

// uint8_t nesCPU::ABX() {
// 	uint8_t lo = read(pc);
// 	pc++;
// 	uint8_t hi = read(pc);
// 	pc++;
// 	addrAbs = (hi << 8) | lo;
// 	addrAbs += x;
// 	if (addrAbs & 0xFF00 != hi << 8) {
// 		return 1; 							// page changed, need one extra clock cycle
// 	}
// 	return 0;
// }

// uint8_t nesCPU::ABY() {
// 	uint8_t lo = read(pc);
// 	pc++;
// 	uint8_t hi = read(pc);
// 	pc++;
// 	addrAbs = (hi << 8) | lo;
// 	addrAbs += y;
// 	if (addrAbs & 0xFF00 != hi << 8) {
// 		return 1; 							// page changed, need one extra clock cycle
// 	}
// 	return 0;
// }

// uint8_t nesCPU::IND() {
// 	uint8_t lo = read(pc);
// 	pc++;
// 	uint8_t hi = read(pc);
// 	pc++;
// 	uint16_t ptr = (hi << 8) | lo;
// 	if (lo == 0xFF) { 						// hardware bug
// 		addrAbs = (read(ptr & 0xFF00) << 8) | read(ptr);
// 	}
// 	else {									// normal case
// 		addrAbs = (read(ptr + 1) << 8) | read(ptr);
// 	}

// 	return 0;	
// }

// uint8_t nesCPU::IZX() {
// 	uint8_t ptr = read(pc);
// 	pc++;
// 	ptr += x;
// 	uint8_t lo = read(0x00FF & (uint16_t) ptr);
// 	uint8_t hi = read(0x00FF & (uint16_t)(ptr + 1)); // Todo: check if ptr overflow wraps around to 0
// 	addrAbs = (hi << 8) | lo;
// 	return 0;
// }

// uint8_t nesCPU::IZY() {
// 	uint16_t ptr = (uint16_t) read(pc);
// 	pc++;
// 	uint8_t lo = read(0x00FF & (uint16_t) ptr);
// 	uint8_t hi = read(0x00FF & (uint16_t)(ptr + 1));
// 	addrAbs = (hi << 8) | lo;
// 	addrAbs += y;
// 	if ((addrAbs & 0xFF00) != (hi << 8)) {
// 		return 1;							// page changed, need one extra clock cycle
// 	}
// 	else {
// 		return 0;
// 	}
// }

// uint8_t nesCPU::ADC() {
// 	fetch();
// 	temp = a + fetched + (uint16_t) getFlag(c);	// add with carry flag
// 	setFlag(c, temp > 255);
// 	setFlag(z, (temp & 0x00FF) == 0);
// 	setFlag(v, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp)) & 0x0080); // what???
// 	setFlag(n, temp & 0x0080);
// 	a = (uint8_t)(temp & 0x00FF);
// 	return 1;								// can require extra clock cycle
// }

// uint8_t nesCPU::AND() {
// 	fetch();
// 	a = a & fetched;
// 	setFlag(z, a == 0);
// 	setFlag(n, a & 0x80);
// 	return 1;
// }

// uint8_t nesCPU::ASL() {
// 	fetch();
// 	temp = (uint16_t) (fetched << 1);
// 	setFlag(c, temp > 255);
// 	setFlag(z, (temp & 0x00FF) == 0);
// 	setFlag(n, temp & 0x0080);
// 	if (opcodeLookup[opcode].addrMode != nesCPU::IMM) {
// 		write(addrAbs, (uint8_t) temp);
// 	}
// 	else {
// 		a = (uint8_t) temp;
// 	}
// 	return 0;
// }

// uint8_t nesCPU::BCC() {
// 	if (getFlag(c) == 0) {
// 		cycles++;
// 		addrAbs = pc + addrRel;
// 		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) {
// 			cycles++;
// 		}
// 		pc = addrAbs;
// 	}
// 	return 1;
// }

// uint8_t nesCPU::BCS() {
// 	if (getFlag(c) == 1) {
// 		cycles++;
// 		addrAbs = pc + addrRel;
// 		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) {
// 			cycles++;
// 		}
// 		pc = addrAbs;
// 	}
// 	return 1;
// }
// uint8_t nesCPU::BEQ() {
// 	if (getFlag(z) == 1) {
// 		cycles++;
// 		addrAbs = pc + addrRel;
// 		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) {
// 			cycles ++;
// 		}
// 		pc = addrAbs;
// 	}
// 	return 1;
// }

// uint8_t nesCPU::BIT() {
// 	fetch();
// 	temp = a & fetched;
// 	if ((temp & 0x00FF) == 0) {
// 		setFlag(z, 1);
// 	}
// 	else {
// 		setFlag(z, 1);
// 	}
// 	setFlag(n, fetched & (1 << 7));
// 	setFlag(v, fetched & (1 << 6));
// 	return 0;
// }

// uint8_t nesCPU::BMI() {
// 	if (getFlag(n) == 1) {
// 		cycles++;
// 		addrAbs = pc + addrRel;
// 		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) {
// 			cycles++;
// 		}
// 		pc = addrAbs;
// 	}
// 	return 1;
// }

// uint8_t nesCPU::BNE() {
// 	if (getFlag(z) == 0) {
// 		cycles++;
// 		addrAbs = pc + addrRel;
// 		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) {
// 			cycles++;
// 		}
// 		pc = addrAbs;
// 	}
// 	return 1;
// }

// uint8_t nesCPU::BPL() {
// 	if (getFlag(n) == 0) {
// 		cycles++;
// 		addrAbs = pc + addrRel;
// 		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) {
// 			cycles++;
// 		}
// 		pc = addrAbs;
// 	}
// 	return 1;
// }

// uint8_t nesCPU::BRK() {
// 	if (getFlag(n) == 0) {
// 		cycles++;
// 		addrAbs = pc + addrRel;
// 		if ((addrAbs & 0xFF00) != (pc & 0xFF00)) {
// 			cycles++;
// 		}
// 		pc = addrAbs;
// 	}
// 	return 1;
// }
