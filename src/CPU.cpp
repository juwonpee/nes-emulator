#include "CPU.h"

void CPU::call(void (CPU::*func)()) {
    (this ->*func)();
}

void CPU::clock() {
    uint8_t opcode = read(PC);
    if (state == finished) { // If available to execute next instruction
        PC++;
        call(lookup[opcode].AddressModeFunction);
        call(lookup[opcode].InstructionFunction);
    }
    else if (state == executing) { // If executing function
        call(lookup[opcode].AddressModeFunction);
    }
}
void CPU::ACC() {
    addressMode = acc;
}
void CPU::ABS() {
    addressMode = abs;
    uint16_t address = read(PC); // Low byte
    PC++;
    address += (read(PC) << 8); // High byte
    PC++;
    finalData = read(address);
}
void CPU::ABX() {
    addressMode = abx;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = read(PC);
    PC++;
    uint16_t address = low + (high << 8);
    address += X;
    finalData = read(address);
    if ((finalData >> 8) != high) { // If the high byte is changed after adding X
        instructionClocks += 1;
    }
}
void CPU::ABY() {
    addressMode = aby;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = read(PC);
    PC++;
    uint16_t address = low + (high << 8);
    address += Y;
    finalData = read(address);
    if ((finalData >> 8) != high) { // If the high byte is changed after adding X
        instructionClocks += 1;
    }
}
void CPU::IMM() {
    addressMode = imm;
    finalData = read(PC);
    PC++;
}
void CPU::IMP() {
    addressMode = imp;
}
void CPU::IND() {
    addressMode = ind;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = read(PC);
    PC++;
    uint16_t address = low + (high << 8); // Get pointer
    low = read(address);
    address++;
    high = read(address);
    address = low + (high << 8); // Get value of pointer
    finalData = read(address);
}
void CPU::XIN() {
    addressMode = xin;
    uint8_t low = read(PC);
    uint8_t high = low + 1;
}
void CPU::YIN() {
    addressMode = yin;
}
void CPU::REL() {
    addressMode = rel;
}
void CPU::ZPG() {
    addressMode = zpg;
}
void CPU::ZPX() {
    addressMode = zpx;
}
void CPU::ZPY() {
    addressMode = zpy;
}
void CPU::AXX() {
    addressMode = axx;
    NOP();
}