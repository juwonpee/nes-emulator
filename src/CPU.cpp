#include "CPU.h"

void CPU::call(void (CPU::*func)()) {
    (this ->*func)();
}

void CPU::clock() {
    uint8_t opcode = read(PC);
    if (instructionClocks == 0) { // If available to execute next instruction
        PC++;
        call(lookup[opcode].AddressModeFunction);
        call(lookup[opcode].InstructionFunction);
    }
    else if (instructionClocks > 0) { // If executing function
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
    finalAddress = address;
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
    finalAddress = address;
    if ((finalData >> 8) != high) { // If the high byte is changed after adding X
        instructionClocks += 1;
    }
}
void CPU::IMM() {
    addressMode = imm;
    finalData = read(PC);
    finalAddress = PC;
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
    finalAddress = address;
}
void CPU::XIN() {
    addressMode = xin;
    uint8_t low = read(PC + X);
    PC++;
    uint8_t high = read(PC + X + 1);
    uint16_t address = low + (high << 8);
    finalData = read(address);
    finalAddress = address;
}
void CPU::YIN() {
    addressMode = yin;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = read(PC + 1);
    uint16_t address = low + (high << 8);
    address += Y;
    finalData = read(address);
    finalAddress = address;
    // TODO:  check if there is carry over page 
    // if ((address & 0xFF00) == (high << 8)) { // If page changes
    //     instructionClocks += 1;
    // }
}
void CPU::REL() {
    addressMode = rel;
    int8_t low = read(PC);
    finalAddress = PC + low;
    instructionClocks++;
    if ((finalAddress & 0xFF00) != (PC & 0xFF00)) instructionClocks++;
}
void CPU::ZPG() {
    addressMode = zpg;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = 0x00;
    uint8_t address = low + (high << 8);
    finalData = read(address);
}
void CPU::ZPX() {
    addressMode = zpx;
    uint8_t low = read(PC);
    uint8_t high = 0x00;
    uint8_t address = low + (high << 8);
    address += X;
    finalData = read(address);
}
void CPU::ZPY() {
    addressMode = zpy;
    uint8_t low = read(PC);
    uint8_t high = 0x00;
    uint8_t address = low + (high << 8);
    address += Y;
    finalData = read(address);
}
void CPU::AXX() {
    addressMode = axx;
    NOP();
}

void CPU::ADC() {
    if (instructionClocks == 0) {
        switch (addressMode) {
            case imm:
                instructionClocks = 2;
            case zpg:
                instructionClocks = 3;
            case zpx:
                instructionClocks = 4;
            case abs:
                instructionClocks = 4;
            case abx:
                instructionClocks += 4;
            case aby:
                instructionClocks += 4;
            case xin:
                instructionClocks = 6;
            case yin:
                instructionClocks += 5;
        }

        uint16_t temp = A + finalData + SR.C;
        A = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = temp & 0x00FF;
        SR.C = temp & 0xFF00;
        // TODO: Implement negative overflow
    }
    instructionClocks--;
}

void CPU::AND() {
    if (instructionClocks == 0) {
        switch (addressMode) {
            case imm:
                instructionClocks = 2;
            case zpg:
                instructionClocks = 3;
            case zpx:
                instructionClocks = 4;
            case abs:
                instructionClocks = 4;
            case abx:
                instructionClocks += 4;
            case aby:
                instructionClocks += 4;
            case xin:
                instructionClocks = 6;
            case yin:
                instructionClocks += 5;
        }

        uint16_t temp = A + finalData;
        A = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = temp & 0x00FF;
    }
    instructionClocks--;
}

void CPU::ASL() {
    if (instructionClocks == 0) {
        switch (addressMode) {
            case acc:
                instructionClocks = 2;
            case zpg:
                instructionClocks = 5;
            case zpx:
                instructionClocks = 6;
            case abs:
                instructionClocks = 6;
            case abx:
                instructionClocks = 7;
        }

        uint16_t temp;
        if (addressMode == acc) {
            temp = A << 1;
            A = temp & 0x00FF;
        }
        else {
            temp = finalData << 1;
            write(finalAddress, temp & 0x00FF);
        }

        SR.N = temp & 0x0080;
        SR.Z = temp & 0x00FF;
        SR.C = temp & 0x0100;
    }
    instructionClocks--;
}

void CPU::BCC() {
    if (instructionClocks == 0) {
        if (!SR.C) PC = finalAddress;
        instructionClocks += 2;
    }
    instructionClocks--;
}

void CPU::BCS() {
    if (instructionClocks == 0) {
        if (SR.C) PC = finalAddress;
        instructionClocks += 2;
    }
    instructionClocks--;
}

void CPU::BEQ() {
    if (instructionClocks == 0) {
        if (SR.Z) PC = finalAddress;
        instructionClocks += 2;
    }
    instructionClocks--;
}

void CPU::BIT() {
    if (instructionClocks == 0) {
        switch (addressMode) {
            case zpg:
                instructionClocks = 3;
            case abs:
                instructionClocks = 4;
        };

        SR.N = finalData & 0x40;
        SR.V = finalData & 0x20;
        SR.Z = finalData & A;
    }
    instructionClocks--;
}

void CPU::BMI() {
    if (instructionClocks == 0) {
        if (SR.N) PC = finalAddress;
        instructionClocks += 2;
    }
    instructionClocks--;
}

void CPU::BNE() {
    if (instructionClocks == 0) {
        if (!SR.Z) PC = finalAddress;
        instructionClocks += 2;
    }
    instructionClocks--;
}

void CPU::BPL() {
    if (instructionClocks == 0) {
        if (!SR.N) PC = finalAddress;
        instructionClocks += 2;
    }
    instructionClocks--;
}

void 