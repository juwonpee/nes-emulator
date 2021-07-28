#include "CPU.h"
#include "BUS.h" // Prevent circular inclusion from BUS class

CPU::CPU(BUS* b) {
    bus = b;
    reset();
}

CPU::~CPU() {
    
}

void CPU::reset() {
    A = 0x00;
    X = 0x00;
    Y = 0x00;
    PC = (read(0xFFFC + 1) << 8) + read(0xFFFC);
    SP = 0x00;
}

CPUstatus CPU::dumpCPU() {
    CPUstatus temp;
    temp.opcode = lookup[opcode].Name;
    temp.instructionClocks = instructionClocks;
    temp.addressMode = addressMode;
    temp.A = A;
    temp.X = X;
    temp.Y = Y;
    temp.SP = SP;
    temp.SR = SR;
    temp.PC = PC;
    return temp;
}

void CPU::call(void (CPU::*func)()) {
    (this ->*func)();
}

void CPU::clock() {
    if (instructionClocks == 0) { // If available to execute next instruction
        opcode = read(PC);
        call(lookup[opcode].AddressModeFunction);
        call(lookup[opcode].InstructionFunction);
        instructionClocks += lookup[opcode].InstructionClocks;
    }
    else if (instructionClocks > 0) { // If executing function
        call(lookup[opcode].InstructionFunction);
    }
}

uint8_t CPU::read(uint16_t address) {
    return bus -> CPUread(address);
}

void CPU::commitMemory() {
    writeQueueStruct temp;
    // Write data to memory when instruction is finished
    if (instructionClocks == 0 || !writeQueue.empty()) { // Sanity check for bugs
        temp = writeQueue.front();
        writeQueue.pop();
        write(temp.address, temp.data);
    }
    else { // Add to queue when instruction is not finished
        throw std::runtime_error("Bug in instruction, Clock not in sync: " + lookup[opcode].Name);
    }
}

void CPU::writeInQueue(uint16_t address, uint8_t data) {
    writeQueueStruct temp;
    temp.address = address;
    temp.data = data;
    writeQueue.emplace(temp);
}

void CPU::write(uint16_t address, uint8_t data) {
    bus -> CPUwrite(address, data);
}


void CPU::ACC() {
    addressMode = acc;
    finalData = A;
    PC++;
}
void CPU::ABS() {
    addressMode = abl;
    PC++;
    uint8_t low = read(PC); // Low byte
    PC++;
    uint8_t high = read(PC); // High byte
    PC++;
    uint16_t address = low + (high << 8);
    finalData = read(address);
}
void CPU::ABX() {
    addressMode = abx;
    PC++;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = read(PC);
    PC++;
    uint16_t address = low + (high << 8);
    address += X;
    finalData = read(address);
    finalAddress = address;
    if ((finalAddress >> 8) != high) { // If the high byte is changed after adding X
        instructionClocks = 1;
    }
}
void CPU::ABY() {
    addressMode = aby;
    PC++;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = read(PC);
    PC++;
    uint16_t address = low + (high << 8);
    address += Y;
    finalData = read(address);
    finalAddress = address;
    if ((finalData >> 8) != high) { // If the high byte is changed after adding X
        instructionClocks = 1;
    }
}
void CPU::IMM() {
    addressMode = imm;
    PC++;
    finalData = read(PC);
    PC++;
}
void CPU::IMP() {
    addressMode = imp;
    PC++;
}
void CPU::IND() {
    addressMode = ind;
    PC++;
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
    PC++;
    uint8_t low = read(PC + X);
    PC++;
    uint8_t high = read(PC + X);
    PC++;
    uint16_t address = low + (high << 8);
    finalData = read(address);
    finalAddress = address;
}
void CPU::YIN() {
    addressMode = yin;
    PC++;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = read(PC);
    PC++;
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
    PC++;
    int8_t low = read(PC);
    finalAddress = PC + low;
    if ((finalAddress & 0xFF00) != (PC & 0xFF00)) instructionClocks = 2;
    PC++; // Increment PC later as there are dependencies
}
void CPU::ZPG() {
    addressMode = zpg;
    PC++;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = 0x00;
    uint8_t address = low + (high << 8);
    finalData = read(address);
}
void CPU::ZPX() {
    addressMode = zpx;
    PC++;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = 0x00;
    uint8_t address = low + (high << 8);
    address += X;
    finalData = read(address);
}
void CPU::ZPY() {
    addressMode = zpy;
    PC++;
    uint8_t low = read(PC);
    PC++;
    uint8_t high = 0x00;
    uint8_t address = low + (high << 8);
    address += Y;
    finalData = read(address);
}
void CPU::AXX() {
    addressMode = axx;
    PC++;
}

void CPU::ADC() {
    if (instructionClocks == 0) {
        uint16_t temp = A + finalData + SR.C;
        A = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
        SR.C = temp & 0xFF00;
        // TODO: Implement negative overflow
    }
    instructionClocks--;
}

void CPU::AND() {
    if (instructionClocks == 0) {
        uint16_t temp = A & finalData;
        A = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
    }
    instructionClocks--;
}

void CPU::ASL() {
    if (instructionClocks == 0) {
        uint16_t temp;
        if (addressMode == acc) {
            temp = A << 1;
            A = temp & 0x00FF;
        }
        else {
            temp = finalData << 1;
            writeInQueue(finalAddress, temp & 0x00FF);
        }

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
        SR.C = temp & 0x0100;
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::BCC() {
    if (instructionClocks == 0) {
        if (!SR.C) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
        }
    }
    instructionClocks--;
}

void CPU::BCS() {
    if (instructionClocks == 0) {
        if (SR.C) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
        }
    }
    instructionClocks--;
}

void CPU::BEQ() {
    if (instructionClocks == 0) {
        if (SR.Z) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
        }
    }
    instructionClocks--;
}

void CPU::BIT() {
    if (instructionClocks == 0) {
        SR.N = finalData & 0x40;
        SR.V = finalData & 0x20;
        SR.Z = finalData & A;
    }
    instructionClocks--;
}

void CPU::BMI() {
    if (instructionClocks == 0) {
        if (SR.N) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
            
        }
    }
    instructionClocks--;
}

void CPU::BNE() {
    if (instructionClocks == 0) {
        if (!SR.Z) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
        }
    }
    instructionClocks--;
}

void CPU::BPL() {
    if (instructionClocks == 0) {
        if (!SR.N) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
        }
    }
    instructionClocks--;
}

void CPU::BRK() { // TODO: Check brk instruction
    if (instructionClocks == 0) {
        uint16_t temp = PC + 2;
        writeInQueue(0x0100 + SP, temp >> 8);
        SP--;
        writeInQueue(0x0100 + SP, temp & 0x00FF);
        SP--;
        writeInQueue(0x0100 + SP, SR.byte);
        SP--;

        SR.I = true;
    }
    instructionClocks --;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::BVC() {
    if (instructionClocks == 0) {
        if (!SR.V) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
        }
    }
    instructionClocks --;
}

void CPU::BVS() {
    if (instructionClocks == 0) {
        if (SR.V) {
            if ((PC-1) & 0xFF00 == finalAddress & 0xFF00) instructionClocks += 1;
            else instructionClocks += 2;
            PC = finalAddress;
        }
    }
    instructionClocks --;
}

void CPU::CLC() {
    if (instructionClocks == 0) {
        SR.C - 0;
    }
    instructionClocks --;
}

void CPU::CLD() {
    if (instructionClocks == 0) {
        SR.D = 0;
    }
    instructionClocks --;
}

void CPU::CLI() {
    if (instructionClocks == 0) {
        SR.I = 0;
    }
    instructionClocks--;
}

void CPU::CLV() {
    if (instructionClocks == 0) {
        SR.V= 0;
    }
    instructionClocks--;
}

void CPU::CMP() {
    if (instructionClocks == 0) {
        if (A < finalData) {
            SR.N = (A-finalData) & 0x0100;
            SR.Z = 0;
            SR.C = 0;
        }
        else if (A == finalData) {
            SR.N = 0;
            SR.Z = 1;
            SR.C = 1;
        }
        else if (A > finalData) {
            SR.N = (A-finalData) & 0x0100;
            SR.Z = 0;
            SR.C = 1;
        }
    }
    instructionClocks--;
}

void CPU::CPX() {
    if (instructionClocks == 0) {
        if (X < finalData) {
            SR.N = (X-finalData) & 0x0100;
            SR.Z = 0;
            SR.C = 0;
        }
        else if (X == finalData) {
            SR.N = 0;
            SR.Z = 1;
            SR.C = 1;
        }
        else if (X > finalData) {
            SR.N = (X-finalData) & 0x0100;
            SR.Z = 0;
            SR.C = 1;
        }
    }
    instructionClocks--;
}

void CPU::CPY() {
    if (instructionClocks == 0) {
        if (Y < finalData) {
            SR.N = (Y-finalData) & 0x0100;
            SR.Z = 0;
            SR.C = 0;
        }
        else if (Y == finalData) {
            SR.N = 0;
            SR.Z = 1;
            SR.C = 1;
        }
        else if (Y > finalData) {
            SR.N = (Y-finalData) & 0x0100;
            SR.Z = 0;
            SR.C = 1;
        }
    }
    instructionClocks--;
}

void CPU::DEC() {
    if (instructionClocks == 0) {
        uint16_t temp = finalData - 1;
        writeInQueue(finalAddress, temp & 0x00FF);
        
        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::DEX() {
    if (instructionClocks == 0) {
        uint16_t temp = X - 1;
        X = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0X00FF);
    }
    instructionClocks--;
}

void CPU::DEY() {
    if (instructionClocks == 0) {
        uint16_t temp = Y - 1;
        Y = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0X00FF);
    }
    instructionClocks--;
}

void CPU::EOR() {
    if (instructionClocks == 0) {
        uint16_t temp = A ^ finalData;
        A = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
    }
    instructionClocks--;
}

void CPU::INC() {
    if (instructionClocks == 0) {
        uint16_t temp = finalData - 1;
        writeInQueue(finalAddress, temp & 0x00FF);

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
        
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::INX() {
    if (instructionClocks == 0) {
        uint16_t temp = X + 1;
        X = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
    }
    instructionClocks--;
}

void CPU::INY() {
    if (instructionClocks == 0) {
        uint16_t temp = Y + 1;
        Y = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
    }
    instructionClocks--;
}

void CPU::JMP() {
    if (instructionClocks == 0) {
        PC = finalAddress;
    }
    instructionClocks--;
}

void CPU::JSR() {
    if (instructionClocks == 0) {
        writeInQueue(0x0100 + SP, PC >> 8);
        SP--;
        writeInQueue(0x0100 + SP, PC & 0x00FF);
        SP--;
        PC = finalAddress;
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::LDA() {
    if (instructionClocks == 0) {
        A = finalData;

        SR.N = finalData & 0x80;
        SR.Z = !(finalData & 0xFF);
    }
    instructionClocks--;
}

void CPU::LDX() {
    if (instructionClocks == 0) {
        X = finalData;

        SR.N = finalData & 0x80;
        SR.Z = !(finalData & 0xFF);
    }
    instructionClocks--;
}

void CPU::LDY() {
    if (instructionClocks == 0) {
        Y = finalData;

        SR.N = finalData & 0x80;
        SR.Z = !(finalData & 0xFF);
    }
    instructionClocks--;
}

void CPU::LSR() {
    if (instructionClocks == 0) {
        uint16_t temp = finalData >> 1;

        SR.N = 0;
        SR.Z = !(temp & 0x00FF);
        SR.C = finalData & 0x01;
    }
    instructionClocks--;
}

void CPU::NOP() {
    if (instructionClocks == 0) {
    }
    instructionClocks--;
}

void CPU::ORA() {
    if (instructionClocks == 0) {
        uint16_t temp = A | finalData;
        A = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
    }
    instructionClocks--;
}

void CPU::PHA() {
    if (instructionClocks == 0) {
        writeInQueue(0x0100 + SP, A);
        SP--;
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::PHP() {
    if (instructionClocks == 0) {
        writeInQueue(0x0100 + SP, SR.byte);
        SP--;
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::PLA() {
    if (instructionClocks == 0) {
        SP++;
        A = read(0x0100 + SP);
    }
    instructionClocks--;
}

void CPU::PLP() {
    if (instructionClocks == 0) {
        SP++;
        uint8_t temp = read(0x0100 + SP);
        SR.N = temp & 0x80;
        SR.V = temp & 0x40;
        SR.B = temp & 0x10;
        SR.D = temp & 0x08;
        SR.I = temp & 0x04;
        SR.Z = temp & 0x02;
        SR.C = temp & 0x01;
    }
    instructionClocks--;
}

void CPU::ROL() {
    if (instructionClocks == 0) {
        uint16_t temp = (finalData << 1) + SR.C;
        if (addressMode == acc) {
            A = temp & 0x00FF;
        }
        else {
            writeInQueue(finalAddress, temp & 0x00FF);
        }

        SR.C = temp & 0x0100;
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::ROR() {
    if (instructionClocks == 0) {
        uint16_t temp = (SR.C >> 7) + (finalData >> 1);

        SR.C = finalData & 0x01;
    }
    instructionClocks--;
}

void CPU::RTI() {
    if (instructionClocks == 0) {
        SP++;
        uint8_t temp = read(0x0100 + SP);
        SR.N = temp & 0x80;
        SR.V = temp & 0x40;
        SR.B = temp & 0x10;
        SR.D = temp & 0x08;
        SR.I = temp & 0x04;
        SR.Z = temp & 0x02;
        SR.C = temp & 0x01;
        SP++;
        PC = read(0x0100 + SP);
        SP++;
        PC = read(0x0100 + SP) << 8;
        PC = temp;
    }
    instructionClocks--;
}

void CPU::RTS() {
    if (instructionClocks == 0) {
        SP++;
        PC = read(0x0100 + SP);
        SP++;
        PC = read(0x0100 + SP) << 8;
        PC++;
    }
    instructionClocks--;
}

void CPU::SBC() {
    if (instructionClocks == 0) {
        uint16_t temp = A - finalData - SR.C;
        A = temp & 0x00FF;

        SR.N = temp & 0x0080;
        SR.Z = !(temp & 0x00FF);
        SR.C = temp & 0x0100;
    }
    instructionClocks--;
}

void CPU::SEC() {
    if (instructionClocks == 0) {
        SR.C = 1;
    }
    instructionClocks--;
}

void CPU::SED() {
    if (instructionClocks == 0) {
        SR.D = 1;
    }
    instructionClocks--;
}

void CPU::SEI() {
    if (instructionClocks == 0) {
        SR.I = 1;
    }
    instructionClocks--;
}

void CPU::STA() {
    if (instructionClocks == 0) {
        writeInQueue(finalAddress, A);
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::STX() {
    if (instructionClocks == 0) {
        writeInQueue(finalAddress, X);
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::STY() {
    if (instructionClocks == 0) {
        writeInQueue(finalAddress, Y);
    }
    instructionClocks--;
    if (instructionClocks == 0) {
        commitMemory();
    }
}

void CPU::TAX() {
    if (instructionClocks == 0) {
        X = A;
        SR.N = X & 0x80;
        SR.Z = !(X & 0xFF);
    }
    instructionClocks--;
}

void CPU::TAY() {
    if (instructionClocks == 0) {
        Y = A;
        SR.N = Y & 0x80;
        SR.Z = !(Y & 0xFF);
    }
    instructionClocks--;
}

void CPU::TSX() {
    if (instructionClocks == 0) {
        X = SP;
        SR.N = X & 0x80;
        SR.Z = !(X & 0xFF);
    }
    instructionClocks--;
}

void CPU::TXA() {
    if (instructionClocks == 0) {
        A = X;
        
        SR.N = X & 0x80;
        SR.Z = !(X & 0xFF);
    }
    instructionClocks--;
}

void CPU::TXS() {
    if (instructionClocks == 0) {
        SP = X;
        SR.N = X & 0x80;
        SR.Z = !(X & 0xFF);
    }
    instructionClocks--;
}

void CPU::TYA() {
    if (instructionClocks == 0) {
        A = Y;
        SR.N = X & 0x80;
        SR.Z = !(X & 0xFF);
    }
    instructionClocks--;
}

void CPU::IXX() {
    NOP();
}