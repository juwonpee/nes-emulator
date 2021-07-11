#pragma once

#include <string>
#include <vector>
#include <queue>

#include "types.h"

class BUS;

class CPU {
    public:
        CPU(BUS* b);
        ~CPU();
        void clock(); // Run one clock

        void reset(); // Force CPU into known state to start execution

        CPUstatus dumpCPU(); // Dump CPU registers for debugging purposes

    private:
        BUS* bus = nullptr;

        uint8_t opcode = 0x00;
        uint8_t A, X, Y, SP = 0x00;
        uint16_t PC = 0x0000;
        SR_t SR;

        uint8_t read(uint16_t address);

        struct writeQueueStruct {
            uint16_t address;
            uint8_t data;
        };
        std::queue<writeQueueStruct> writeQueue;
        void commitMemory();
        void writeInQueue(uint16_t address, uint8_t data);
        void write(uint16_t address, uint8_t data);


        /* Helper variables*/
        void call(void (CPU::*func)()); // Function to help call other functions in this class
        uint8_t finalData = 0x00; // Final data to instruction
        uint16_t finalAddress = 0x0000;
        uint8_t instructionClocks = 0x00; // Number of clocks left on instruction
        struct Instruction {
            std::string Name;
            void (CPU::*AddressModeFunction) (void) = nullptr;
            void (CPU::*InstructionFunction) (void) = nullptr;
        };
        std::vector<Instruction> lookup  =
        {
            //                                  0xXX01                               0xXX02                             0xXX03                              0xXX04                              0xXX05                              0xXX06                              0xXX07                              0xXX08                              0xXX09                              0xXX0a                              0xXX0b                              0xXX0c                              0xXX0d                              0xXX0e                              0xXX0f
            {"BRK: 0x00", &CPU::IMP, &CPU::BRK}, {"ORA: 0x01", &CPU::XIN, &CPU::ORA}, {"XXX: 0x02", &CPU::AXX, &CPU::IXX}, {"XXX: 0x03", &CPU::AXX, &CPU::IXX}, {"XXX: 0x04", &CPU::AXX, &CPU::IXX}, {"ORA: 0x05", &CPU::ZPG, &CPU::ORA}, {"ASL: 0x06", &CPU::ZPG, &CPU::ASL}, {"XXX: 0x07", &CPU::AXX, &CPU::IXX}, {"PHP: 0x08", &CPU::IMP, &CPU::PHP}, {"ORA: 0x09", &CPU::IMM, &CPU::ORA}, {"ASL: 0x0A", &CPU::ACC, &CPU::ASL}, {"XXX: 0x0B", &CPU::AXX, &CPU::IXX}, {"XXX: 0x0C", &CPU::AXX, &CPU::IXX}, {"ORA: 0x0D", &CPU::ABS, &CPU::ORA}, {"ASL: 0x0E", &CPU::ABS, &CPU::ASL}, {"XXX: 0x0F", &CPU::AXX, &CPU::IXX}, 
            {"BPL: 0x10", &CPU::REL, &CPU::BPL}, {"ORA: 0x11", &CPU::YIN, &CPU::ORA}, {"XXX: 0x12", &CPU::AXX, &CPU::IXX}, {"XXX: 0x13", &CPU::AXX, &CPU::IXX}, {"XXX: 0x14", &CPU::AXX, &CPU::IXX}, {"ORA: 0x15", &CPU::ZPX, &CPU::ORA}, {"ASL: 0x16", &CPU::ZPX, &CPU::ASL}, {"XXX: 0x17", &CPU::AXX, &CPU::IXX}, {"CLC: 0x18", &CPU::IMP, &CPU::CLC}, {"ORA: 0x19", &CPU::ABY, &CPU::ORA}, {"XXX: 0x1A", &CPU::AXX, &CPU::IXX}, {"XXX: 0x1B", &CPU::AXX, &CPU::IXX}, {"XXX: 0x1C", &CPU::AXX, &CPU::IXX}, {"ORA: 0x1D", &CPU::ABX, &CPU::ORA}, {"ASL: 0x1E", &CPU::ABX, &CPU::ASL}, {"XXX: 0x1F", &CPU::AXX, &CPU::IXX}, 
            {"JSR: 0x20", &CPU::REL, &CPU::JSR}, {"AND: 0x21", &CPU::XIN, &CPU::AND}, {"XXX: 0x22", &CPU::AXX, &CPU::IXX}, {"XXX: 0x23", &CPU::AXX, &CPU::IXX}, {"BIT: 0x24", &CPU::ZPG, &CPU::BIT}, {"AND: 0x25", &CPU::ZPG, &CPU::AND}, {"ROL: 0x26", &CPU::ZPG, &CPU::ROL}, {"XXX: 0x27", &CPU::AXX, &CPU::IXX}, {"PLP: 0x28", &CPU::IMP, &CPU::PLP}, {"AND: 0x29", &CPU::IMM, &CPU::AND}, {"ROL: 0x2A", &CPU::ACC, &CPU::ROL}, {"XXX: 0x2B", &CPU::AXX, &CPU::IXX}, {"BIT: 0x2C", &CPU::ABS, &CPU::BIT}, {"AND: 0x2D", &CPU::ABX, &CPU::AND}, {"ROL: 0x2E", &CPU::ABX, &CPU::ROL}, {"XXX: 0x2F", &CPU::AXX, &CPU::IXX}, 
            {"BMI: 0x30", &CPU::REL, &CPU::BMI}, {"AND: 0x31", &CPU::YIN, &CPU::AND}, {"XXX: 0x32", &CPU::AXX, &CPU::IXX}, {"XXX: 0x33", &CPU::AXX, &CPU::IXX}, {"XXX: 0x34", &CPU::AXX, &CPU::IXX}, {"AND: 0x35", &CPU::ZPX, &CPU::AND}, {"ROL: 0x36", &CPU::ZPG, &CPU::ROL}, {"XXX: 0x37", &CPU::AXX, &CPU::IXX}, {"SEC: 0x38", &CPU::IMP, &CPU::SEC}, {"AND: 0x39", &CPU::ABY, &CPU::AND}, {"XXX: 0x3A", &CPU::AXX, &CPU::IXX}, {"XXX: 0x3B", &CPU::AXX, &CPU::IXX}, {"XXX: 0x3C", &CPU::AXX, &CPU::IXX}, {"AND: 0x3D", &CPU::ABX, &CPU::AND}, {"ROL: 0x3E", &CPU::ABX, &CPU::ROL}, {"XXX: 0x3F", &CPU::AXX, &CPU::IXX}, 
            {"RTI: 0x40", &CPU::IMP, &CPU::RTI}, {"EOR: 0x41", &CPU::XIN, &CPU::EOR}, {"XXX: 0x42", &CPU::AXX, &CPU::IXX}, {"XXX: 0x43", &CPU::AXX, &CPU::IXX}, {"XXX: 0x44", &CPU::AXX, &CPU::IXX}, {"EOR: 0x45", &CPU::ZPG, &CPU::EOR}, {"LSR: 0x46", &CPU::ZPG, &CPU::LSR}, {"XXX: 0x47", &CPU::AXX, &CPU::IXX}, {"PHA: 0x48", &CPU::IMP, &CPU::PHA}, {"EOR: 0x49", &CPU::IMM, &CPU::EOR}, {"LSR: 0x4A", &CPU::ACC, &CPU::LSR}, {"XXX: 0x4B", &CPU::AXX, &CPU::IXX}, {"JMP: 0x4C", &CPU::ABS, &CPU::JMP}, {"EOR: 0x4D", &CPU::ABS, &CPU::EOR}, {"LSR: 0x4E", &CPU::ABS, &CPU::LSR}, {"XXX: 0x4F", &CPU::AXX, &CPU::IXX}, 
            {"BVC: 0x50", &CPU::REL, &CPU::BVC}, {"EOR: 0x51", &CPU::XIN, &CPU::EOR}, {"XXX: 0x52", &CPU::AXX, &CPU::IXX}, {"XXX: 0x53", &CPU::AXX, &CPU::IXX}, {"XXX: 0x54", &CPU::AXX, &CPU::IXX}, {"EOR: 0x55", &CPU::ZPX, &CPU::EOR}, {"LSR: 0x56", &CPU::ZPX, &CPU::LSR}, {"XXX: 0x57", &CPU::AXX, &CPU::IXX}, {"CLI: 0x58", &CPU::IMP, &CPU::CLI}, {"EOR: 0x59", &CPU::ABY, &CPU::EOR}, {"XXX: 0x5A", &CPU::AXX, &CPU::IXX}, {"XXX: 0x5B", &CPU::AXX, &CPU::IXX}, {"XXX: 0x5C", &CPU::AXX, &CPU::IXX}, {"EOR: 0x5D", &CPU::ABX, &CPU::EOR}, {"LSR: 0x5E", &CPU::ABX, &CPU::LSR}, {"XXX: 0x5F", &CPU::AXX, &CPU::IXX}, 
            {"RTS: 0x60", &CPU::IMP, &CPU::RTS}, {"ADC: 0x61", &CPU::XIN, &CPU::ADC}, {"XXX: 0x62", &CPU::AXX, &CPU::IXX}, {"XXX: 0x63", &CPU::AXX, &CPU::IXX}, {"XXX: 0x64", &CPU::AXX, &CPU::IXX}, {"ADC: 0x65", &CPU::ZPG, &CPU::ADC}, {"ROR: 0x66", &CPU::ZPG, &CPU::ROR}, {"XXX: 0x67", &CPU::AXX, &CPU::IXX}, {"PLA: 0x68", &CPU::IMP, &CPU::PLA}, {"ADC: 0x69", &CPU::IMM, &CPU::ADC}, {"ROR: 0x6A", &CPU::ACC, &CPU::ROR}, {"XXX: 0x6B", &CPU::AXX, &CPU::IXX}, {"JMP: 0x6C", &CPU::IND, &CPU::JMP}, {"ADC: 0x6D", &CPU::ABS, &CPU::ADC}, {"ROR: 0x6E", &CPU::ABS, &CPU::ROR}, {"XXX: 0x6F", &CPU::AXX, &CPU::IXX}, 
            {"BVS: 0x70", &CPU::REL, &CPU::BVS}, {"ADC: 0x71", &CPU::YIN, &CPU::ADC}, {"XXX: 0x72", &CPU::AXX, &CPU::IXX}, {"XXX: 0x73", &CPU::AXX, &CPU::IXX}, {"XXX: 0x74", &CPU::AXX, &CPU::IXX}, {"ADC: 0x75", &CPU::ZPX, &CPU::ADC}, {"ROR: 0x76", &CPU::ZPX, &CPU::ROR}, {"XXX: 0x77", &CPU::AXX, &CPU::IXX}, {"SEI: 0x78", &CPU::IMP, &CPU::SEI}, {"ADC: 0x79", &CPU::ABY, &CPU::ADC}, {"XXX: 0x7A", &CPU::AXX, &CPU::IXX}, {"XXX: 0x7B", &CPU::AXX, &CPU::IXX}, {"XXX: 0x7C", &CPU::AXX, &CPU::IXX}, {"ADC: 0x7D", &CPU::ABX, &CPU::ADC}, {"ROR: 0x7E", &CPU::ABX, &CPU::ROR}, {"XXX: 0x7F", &CPU::AXX, &CPU::IXX}, 
            {"XXX: 0x80", &CPU::AXX, &CPU::IXX}, {"STA: 0x81", &CPU::XIN, &CPU::STA}, {"XXX: 0x82", &CPU::AXX, &CPU::IXX}, {"XXX: 0x83", &CPU::AXX, &CPU::IXX}, {"STY: 0x84", &CPU::ZPG, &CPU::STY}, {"STA: 0x85", &CPU::ZPG, &CPU::STA}, {"STX: 0x86", &CPU::ZPG, &CPU::STX}, {"XXX: 0x87", &CPU::AXX, &CPU::IXX}, {"DEY: 0x88", &CPU::IMP, &CPU::DEY}, {"XXX: 0x89", &CPU::AXX, &CPU::IXX}, {"TXA: 0x8A", &CPU::IMP, &CPU::TXA}, {"XXX: 0x8B", &CPU::AXX, &CPU::IXX}, {"STY: 0x8C", &CPU::ABS, &CPU::STY}, {"STA: 0x8D", &CPU::ABS, &CPU::STA}, {"STX: 0x8E", &CPU::ABS, &CPU::STX}, {"XXX: 0x8F", &CPU::AXX, &CPU::IXX}, 
            {"BCC: 0x90", &CPU::REL, &CPU::BCC}, {"STA: 0x91", &CPU::YIN, &CPU::STA}, {"XXX: 0x92", &CPU::AXX, &CPU::IXX}, {"XXX: 0x93", &CPU::AXX, &CPU::IXX}, {"STY: 0x94", &CPU::ZPX, &CPU::STY}, {"STA: 0x95", &CPU::ZPX, &CPU::STA}, {"STX: 0x96", &CPU::ZPX, &CPU::STX}, {"XXX: 0x97", &CPU::AXX, &CPU::IXX}, {"TYA: 0x98", &CPU::IMP, &CPU::TYA}, {"STA: 0x99", &CPU::ABY, &CPU::STA}, {"TXS: 0x9A", &CPU::IMP, &CPU::TXS}, {"XXX: 0x9B", &CPU::AXX, &CPU::IXX}, {"XXX: 0x9C", &CPU::AXX, &CPU::IXX}, {"STA: 0x9D", &CPU::ABX, &CPU::STA}, {"XXX: 0x9E", &CPU::AXX, &CPU::IXX}, {"XXX: 0x9F", &CPU::AXX, &CPU::IXX}, 
            {"LDY: 0xA0", &CPU::IMM, &CPU::LDY}, {"LDA: 0xA1", &CPU::YIN, &CPU::LDA}, {"LDX: 0xA2", &CPU::IMM, &CPU::LDX}, {"XXX: 0xA3", &CPU::AXX, &CPU::IXX}, {"LDY: 0xA4", &CPU::ZPG, &CPU::LDY}, {"LDA: 0xA5", &CPU::ZPG, &CPU::LDA}, {"LDX: 0xA6", &CPU::ZPG, &CPU::LDX}, {"XXX: 0xA7", &CPU::AXX, &CPU::IXX}, {"TAY: 0xA8", &CPU::IMP, &CPU::TAY}, {"LDA: 0xA9", &CPU::IMM, &CPU::LDA}, {"TAX: 0xAA", &CPU::IMP, &CPU::TAX}, {"XXX: 0xAB", &CPU::AXX, &CPU::IXX}, {"LDY: 0xAC", &CPU::ABS, &CPU::LDY}, {"LDA: 0xAD", &CPU::ABS, &CPU::LDA}, {"LDX: 0xAE", &CPU::ABS, &CPU::LDX}, {"XXX: 0xAF", &CPU::AXX, &CPU::IXX}, 
            {"BCS: 0xB0", &CPU::REL, &CPU::BCS}, {"LDA: 0xB1", &CPU::YIN, &CPU::LDA}, {"XXX: 0xB2", &CPU::AXX, &CPU::IXX}, {"XXX: 0xB3", &CPU::AXX, &CPU::IXX}, {"LDY: 0xB4", &CPU::ZPX, &CPU::LDY}, {"LDA: 0xB5", &CPU::ZPX, &CPU::LDA}, {"LDX: 0xB6", &CPU::ZPX, &CPU::LDX}, {"XXX: 0xB7", &CPU::AXX, &CPU::IXX}, {"CLV: 0xB8", &CPU::IMP, &CPU::CLV}, {"LDA: 0xB9", &CPU::ABY, &CPU::LDA}, {"TSX: 0xBA", &CPU::IMP, &CPU::TSX}, {"XXX: 0xBB", &CPU::AXX, &CPU::IXX}, {"LDY: 0xBC", &CPU::ABX, &CPU::LDY}, {"LDA: 0xBD", &CPU::ABX, &CPU::LDA}, {"LDX: 0xBE", &CPU::ABX, &CPU::LDX}, {"XXX: 0xBF", &CPU::AXX, &CPU::IXX}, 
            {"CPY: 0xC0", &CPU::REL, &CPU::CPY}, {"CMP: 0xC1", &CPU::XIN, &CPU::CMP}, {"XXX: 0xC2", &CPU::AXX, &CPU::IXX}, {"XXX: 0xC3", &CPU::AXX, &CPU::IXX}, {"CPY: 0xC4", &CPU::ZPG, &CPU::CPY}, {"CMP: 0xC5", &CPU::ZPG, &CPU::CMP}, {"DEC: 0xC6", &CPU::ZPG, &CPU::DEC}, {"XXX: 0xC7", &CPU::AXX, &CPU::IXX}, {"INY: 0xC8", &CPU::IMP, &CPU::INY}, {"CMP: 0xC9", &CPU::IMM, &CPU::CMP}, {"DEX: 0xCA", &CPU::IMP, &CPU::DEX}, {"XXX: 0xCB", &CPU::AXX, &CPU::IXX}, {"CPY: 0xCC", &CPU::ABS, &CPU::CPY}, {"CMP: 0xCD", &CPU::ABS, &CPU::CMP}, {"DEC: 0xCE", &CPU::ABS, &CPU::DEC}, {"XXX: 0xCF", &CPU::AXX, &CPU::IXX}, 
            {"BNE: 0xD0", &CPU::REL, &CPU::BNE}, {"CMP: 0xD1", &CPU::XIN, &CPU::CMP}, {"XXX: 0xD2", &CPU::AXX, &CPU::IXX}, {"XXX: 0xD3", &CPU::AXX, &CPU::IXX}, {"XXX: 0xD4", &CPU::AXX, &CPU::IXX}, {"CMP: 0xD5", &CPU::ZPX, &CPU::CMP}, {"DEC: 0xD6", &CPU::ZPX, &CPU::DEC}, {"XXX: 0xD7", &CPU::AXX, &CPU::IXX}, {"CLD: 0xD8", &CPU::IMP, &CPU::CLD}, {"CMP: 0xD9", &CPU::ABY, &CPU::CMP}, {"XXX: 0xDA", &CPU::AXX, &CPU::IXX}, {"XXX: 0xDB", &CPU::AXX, &CPU::IXX}, {"XXX: 0xDC", &CPU::AXX, &CPU::IXX}, {"CMP: 0xDD", &CPU::ABX, &CPU::CMP}, {"DEC: 0xDE", &CPU::ABX, &CPU::DEC}, {"XXX: 0xDF", &CPU::AXX, &CPU::IXX}, 
            {"CPX: 0xE0", &CPU::IMM, &CPU::CPX}, {"SBC: 0xE1", &CPU::XIN, &CPU::SBC}, {"XXX: 0xE2", &CPU::AXX, &CPU::IXX}, {"XXX: 0xE3", &CPU::AXX, &CPU::IXX}, {"CPX: 0xE4", &CPU::ZPG, &CPU::CPX}, {"SBC: 0xE5", &CPU::ZPG, &CPU::SBC}, {"INC: 0xE6", &CPU::ZPG, &CPU::INC}, {"XXX: 0xE7", &CPU::AXX, &CPU::IXX}, {"INX: 0xE8", &CPU::IMP, &CPU::INX}, {"SBC: 0xE9", &CPU::IMM, &CPU::SBC}, {"NOP: 0xEA", &CPU::IMP, &CPU::NOP}, {"XXX: 0xEB", &CPU::AXX, &CPU::IXX}, {"CPX: 0xEC", &CPU::ABS, &CPU::CPX}, {"SBC: 0xED", &CPU::ABS, &CPU::SBC}, {"INC: 0xEE", &CPU::ABS, &CPU::INC}, {"XXX: 0xEF", &CPU::AXX, &CPU::IXX}, 
            {"BEQ: 0xF0", &CPU::REL, &CPU::BEQ}, {"SBC: 0xF1", &CPU::YIN, &CPU::SBC}, {"XXX: 0xF2", &CPU::AXX, &CPU::IXX}, {"XXX: 0xF3", &CPU::AXX, &CPU::IXX}, {"XXX: 0xF4", &CPU::AXX, &CPU::IXX}, {"SBC: 0xF5", &CPU::ZPX, &CPU::SBC}, {"INC: 0xF6", &CPU::ZPX, &CPU::INC}, {"XXX: 0xF7", &CPU::AXX, &CPU::IXX}, {"SED: 0xF8", &CPU::IMP, &CPU::SED}, {"SBC: 0xF9", &CPU::ABY, &CPU::SBC}, {"XXX: 0xFA", &CPU::AXX, &CPU::IXX}, {"XXX: 0xFB", &CPU::AXX, &CPU::IXX}, {"XXX: 0xFC", &CPU::AXX, &CPU::IXX}, {"SBC: 0xFD", &CPU::ABX, &CPU::SBC}, {"INC: 0xFE", &CPU::ABX, &CPU::INC}, {"XXX: 0xFF", &CPU::AXX, &CPU::IXX}, 
        };
        
        // Addressing modes
        addressingMode addressMode;
        // operand is AC (implied single byte instruction)
        void ACC();
        // abs......absolute..............OPC $LLHH......operand is address $HHLL *
        void ABS();
        // abs,X....absolute, X-indexed...OPC $LLHH,X....operand is address; effective address is address incremented by X with carry **
        void ABX();
        // abs,Y....absolute, Y-indexed...OPC $LLHH,Y....operand is address; effective address is address incremented by Y with carry **
        void ABY();
        // # .......immediate.............OPC #$BB.......operand is byte BB
        void IMM();
        // impl.....implied...............OPC............operand implied
        void IMP();
        // ind......indirect..............OPC ($LLHH)....operand is address; effective address is contents of word at address: C.w($HHLL)
        void IND();
        // X,ind....X-indexed, indirect...OPC ($LL,X)....operand is zeropage address; effective address is word in (LL + X, LL + X + 1), inc. without carry: C.w($00LL + X)
        void XIN();
        // ind,Y....indirect, Y-indexed...OPC ($LL),Y....operand is zeropage address; effective address is word in (LL, LL + 1) incremented by Y with carry: C.w($00LL) + Y
        void YIN();
        // rel......relative..............OPC $BB........branch target is PC + signed offset BB ***
        void REL();
        // zpg......zeropage..............OPC $LL........operand is zeropage address (hi-byte is zero, address = $00LL)
        void ZPG();
        // zpg,X	zeropage, X-indexed	OPC $LL,X	operand is zeropage address; effective address is address incremented by X without carry **
        void ZPX();
        // zpg,Y	zeropage, Y-indexed	OPC $LL,Y	operand is zeropage address; effective address is address incremented by Y without carry **
        void ZPY();
        // Illegal or hidden instruction, identical to NOP
        void AXX();
        // *
        // 16-bit address words are little endian, lo(w)-byte first, followed by the hi(gh)-byte.
        // (An assembler will use a human readable, big-endian notation as in $HHLL.)

        // **
        // The available 16-bit address space is conceived as consisting of pages of 256 bytes each, with
        // address hi-bytes represententing the page index. An increment with carry may affect the hi-byte
        // and may thus result in a crossing of page boundaries, adding an extra cycle to the execution.
        // Increments without carry do not affect the hi-byte of an address and no page transitions do occur.
        // Generally, increments of 16-bit addresses include a carry, increments of zeropage addresses don't.
        // Notably this is not related in any way to the state of the carry bit of the accumulator.

        // ***
        // Branch offsets are signed 8-bit values, -128 ... +127, negative offsets in two's complement.
        // Page transitions may occur and add an extra cycle to the exucution.


        // Instructions

        // Add Memory to Accumulator with Carry
        // A + M + C -> A, C
        // N Z C I D V
        // + + + - - +
        // addressing   assembler       opc     bytes   cyles
        // immediate	ADC #oper       69      2       2  
        // zeropage	    ADC oper        65	    2	    3  
        // zeropage,X	ADC oper,X	    75      2       4  
        // absolute	    ADC oper        6D      3       4  
        // absolute,X	ADC oper,X	    7D	    3	    4* 
        // absolute,Y	ADC oper,Y	    79	    3	    4* 
        // (indirect,X)	ADC (oper,X)    61	    2	    6  
        // (indirect),Y	ADC (oper),Y	71	    2	    5*
        void ADC();
        
        // AND Memory with Accumulator
        // A AND M -> A
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	AND #oper	    29	    2	    2  
        // zeropage	    AND oper        25	    2   	3  
        // zeropage,X	AND oper,X	    35	    2   	4  
        // absolute	    AND oper	    2D	    3	    4  
        // absolute,X	AND oper,X	    3D	    3	    4* 
        // absolute,Y	AND oper,Y	    39	    3	    4* 
        // (indirect,X)	AND (oper,X)	21	    2	    6  
        // (indirect),Y	AND (oper),Y	31	    2	    5*
        void AND();

        // Shift Left One Bit (Memory or Accumulator)
        // C <- [76543210] <- 0
        // N Z C I D V
        // + + + - - -
        // addressing	assembler	    opc	    bytes	cyles
        // accumulator	ASL A	        0A	    1	    2  
        // zeropage	    ASL oper        06	    2	    5  
        // zeropage,X	ASL oper,X	    16	    2	    6  
        // absolute	    ASL oper	    0E	    3	    6  
        // absolute,X	ASL oper,X	    1E	    3	    7  
        void ASL();

        // Branch on Carry Clear
        // branch on C = 0
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BCC oper	    90	    2	    2**
        void BCC();

        // Branch on Carry Set
        // branch on C = 1
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BCS oper	    B0	    2	    2**
        void BCS();

        // Branch on Result Zero
        // branch on Z = 1
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BEQ oper	    F0	    2	    2**
        void BEQ();

        // Test Bits in Memory with Accumulator
        // bits 7 and 6 of operand are transfered to bit 7 and 6 of SR (N,V);
        // the zero-flag is set to the result of operand AND accumulator.
        // A AND M, M7 -> N, M6 -> V
        // N  Z  C  I  D  V
        // M7 +	 -	-  -  M6
        // addressing	assembler	    opc     bytes	cyles
        // zeropage	    BIT oper	    24	    2	    3  
        // absolute	    BIT oper    	2C	    3	    4 
        void BIT();

        
        // Branch on Result Minus
        // branch on N = 1
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BMI oper	    30	    2	    2**
        void BMI();

        // Branch on Result not Zero
        // branch on Z = 0
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BNE oper	    D0	    2	    2**
        void BNE();

        // Branch on Result Plus
        // branch on N = 0
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BPL oper	    10	    2	    2**
        void BPL();
        
        // Force Break
        // interrupt,
        // push PC+2, push SR
        // N Z C I D V
        // - - - 1 - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    BRK 00	        1	    1	    7  
        void BRK();

        // Branch on Overflow Clear
        // branch on V = 0
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BVC oper	    50	    2	    2**
        void BVC();

        // Branch on Overflow Set
        // branch on V = 1
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // relative	    BVC oper	    70	    2	    2**
        void BVS();

        // Clear Carry Flag
        // 0 -> C
        // N Z C I D V
        // - - 0 - - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    CLC	            18	    1	    2  
        void CLC();

        // Clear Decimal Mode
        // 0 -> D
        // N Z C I D V
        // - - - - 0 -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    CLD	            D8	    1	    2  
        void CLD();

        // Clear Interrupt Disable Bit
        // 0 -> I
        // N Z C I D V
        // - - - 0 - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    CLI	            58	    1	    2  
        void CLI();


        // Clear Overflow Flag
        // 0 -> V
        // N Z C I D V
        // - - - - - 0
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    CLV	            B8	    1	    2  
        void CLV();

        // Compare Memory with Accumulator
        // A - M
        // N Z C I D V
        // + + + - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	CMP #oper	    C9	    2	    2  
        // zeropage	    CMP oper	    C5	    2	    3  
        // zeropage,X	CMP oper,X	    D5	    2	    4  
        // absolute	    CMP oper	    CD	    3	    4  
        // absolute,X	CMP oper,X	    DD	    3	    4* 
        // absolute,Y	CMP oper,Y	    D9	    3	    4* 
        // (indirect,X)	CMP (oper,X)	C1	    2	    6  
        // (indirect),Y	CMP (oper),Y	D1	    2	    5* 
        void CMP();

        // Compare Memory and Index X
        // X - M
        // N Z C I D V
        // + + + - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	CPX #oper	    E0	    2	    2  
        // zeropage	    CPX oper	    E4	    2	    3  
        // absolute	    CPX oper	    EC  	3	    4  
        void CPX();

        // Compare Memory and Index Y
        // Y - M
        // N Z C I D V
        // + + + - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	CPY #oper	    C0	    2	    2  
        // zeropage	    CPY oper	    C4	    2	    3  
        // absolute	    CPY oper	    CC	    3	    4  
        void CPY();

        // Decrement Memory by One
        // M - 1 -> M
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // zeropage	    DEC oper	    C6	    2	    5  
        // zeropage,X	DEC oper,X	    D6	    2	    6  
        // absolute	    DEC oper	    CE	    3	    6  
        // absolute,X	DEC oper,X	    DE	    3	    7  
        void DEC();

        // Decrement Index X by One
        // X - 1 -> X
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    DEX	            CA	    1	    2  
        void DEX();

        // Decrement Index Y by One
        // Y - 1 -> Y
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    DEY	            CA	    1	    2  
        void DEY();

        // Exclusive-OR Memory with Accumulator
        // A EOR M -> A
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	EOR #oper	    49	    2	    2  
        // zeropage	    EOR oper	    45	    2	    3  
        // zeropage,X	EOR oper,X	    55	    2	    4  
        // absolute	    EOR oper	    4D	    3	    4  
        // absolute,X	EOR oper,X	    5D	    3	    4* 
        // absolute,Y	EOR oper,Y	    59	    3	    4* 
        // (indirect,X)	EOR (oper,X)	41	    2	    6  
        // (indirect),Y	EOR (oper),Y	51	    2	    5* 
        void EOR();

        // Increment Memory by One
        // M + 1 -> M
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // zeropage	    INC oper	    E6	    2	    5  
        // zeropage,X	INC oper,X	    F6	    2	    6  
        // absolute	    INC oper	    EE	    3	    6  
        // absolute,X	INC oper,X	    FE	    3	    7  
        void INC();


        // Increment Index X by One
        // X + 1 -> X
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    INX	            E8	    1	    2  
        void INX();

        // Increment Index Y by One
        // Y + 1 -> Y
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    INY	            C8	    1	    2  
        void INY();

        // Jump to New Location
        // (PC+1) -> PCL
        // (PC+2) -> PCH
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // absolute	    JMP oper	    4C	    3	    3  
        // indirect	    JMP (oper)	    6C	    3	    5  
        void JMP();

        // Jump to New Location Saving Return Address
        // push (PC+2),
        // (PC+1) -> PCL
        // (PC+2) -> PCH
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // absolute	    JSR oper	    20	    3	    6  
        void JSR();


        // Load Accumulator with Memory
        // M -> A
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	LDA #oper	    A9	    2	    2  
        // zeropage	    LDA oper	    A5	    2	    3  
        // zeropage,X	LDA oper,X	    B5	    2	    4  
        // absolute	    LDA oper	    AD	    3	    4  
        // absolute,X	LDA oper,X	    BD	    3	    4* 
        // absolute,Y	LDA oper,Y	    B9	    3	    4* 
        // (indirect,X)	LDA (oper,X)	A1	    2	    6  
        // (indirect),Y	LDA (oper),Y	B1	    2	    5* 
        void LDA();

        // Load Index X with Memory
        // M -> X
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	LDX #oper	    A2	    2	    2  
        // zeropage	    LDX oper        A6	    2	    3  
        // zeropage,Y	LDX oper,Y	    B6	    2	    4  
        // absolute	    LDX oper        AE	    3	    4  
        // absolute,Y	LDX oper,Y	    BE	    3	    4* 
        void LDX();

        // Load Index Y with Memory
        // M -> Y
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	LDY #oper	    A0	    2	    2  
        // zeropage	    LDY oper	    A4	    2	    3  
        // zeropage,X	LDY oper,X	    B4	    2	    4  
        // absolute	    LDY oper	    AC	    3	    4  
        // absolute,X	LDY oper,X	    BC	    3	    4* 
        void LDY();

        // Shift One Bit Right (Memory or Accumulator)
        // 0 -> [76543210] -> C
        // N Z C I D V
        // 0 + + - - -
        // addressing	assembler	    opc	    bytes	cyles
        // accumulator	LSR A	        4A	    1	    2  
        // zeropage	    LSR oper	    46	    2	    5  
        // zeropage,X	LSR oper,X	    56	    2	    6  
        // absolute 	LSR oper	    4E	    3	    6  
        // absolute,X	LSR oper,X	    5E	    3	    7  
        void LSR();

        // No Operation
        // ---
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // implied	    NOP	            EA	    1	    2  
        void NOP();

        // OR Memory with Accumulator
        // A OR M -> A
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	    opc	    bytes	cyles
        // immediate	ORA #oper	    09	    2       2  
        // zeropage	    ORA oper	    05	    2	    3  
        // zeropage,X	ORA oper,X	    15	    2	    4  
        // absolute	    ORA oper	    0D	    3	    4  
        // absolute,X	ORA oper,X	    1D	    3	    4* 
        // absolute,Y	ORA oper,Y	    19	    3	    4* 
        // (indirect,X)	ORA (oper,X)	01	    2	    6  
        // (indirect),Y	ORA (oper),Y	11	    2	    5* 
        void ORA();

        // Push Accumulator on Stack
        // push A
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    PHA	        48	    1	    3  
        void PHA();

        // Pushytes Processor Status on Stack
        // push SR
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	opc	    b	cyles
        // implied	    PHP	        08	    1	    3  
        void PHP();

        // Pull Accumulator from Stack
        // pull A
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    PLA	        68	    1	    4  
        void PLA();

        // Pull Processor Status from Stack
        // pull SR
        // N Z C I D V
        // from stack
        // addressing	assembler	opc	    bytes	cyles
        // implied	    PLP	        28	    1	    4  
        void PLP();

        // Rotate One Bit Left (Memory or Accumulator)
        // C <- [76543210] <- C
        // N Z C I D V
        // + + + - - -
        // addressing	assembler	opc	    bytes	cyles
        // accumulator	ROL A	    2A	    1	    2  
        // zeropage	    ROL oper	26	    2	    5  
        // zeropage,X	ROL oper,X	36	    2	    6  
        // absolute	    ROL oper	2E	    3	    6  
        // absolute,X	ROL oper,X	3E	    3	    7  
        void ROL();

        // Rotate One Bit Right (Memory or Accumulator)
        // C -> [76543210] -> C
        // N Z C I D V
        // + + + - - -
        // addressing	assembler	opc	    bytes	cyles
        // accumulator	ROR A	    6A	    1	    2  
        // zeropage	    ROR oper	66	    2	    5  
        // zeropage,X	ROR oper,X	76	    2	    6  
        // absolute	    ROR oper	6E	    3	    6  
        // absolute,X	ROR oper,X	7E	    3	    7  
        void ROR();

        // Return from Interrupt
        // pull SR, pull PC
        // N Z C I D V
        // from stack
        // addressing	assembler	opc	    bytes	cyles
        // implied	    RTI	        40	    1	    6  
        void RTI();

        // Return from Subroutine
        // pull PC, PC+1 -> PC
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    RTS	        60	    1	    6  
        void RTS();

        // Subtract Memory from Accumulator with Borrow
        // A - M - C -> A
        // N Z C I D V
        // + + + - - +
        // addressing	assembler	opc	    bytes	cyles
        // immediate	SBC #oper	E9	    2	    2  
        // zeropage	    SBC oper	E5	    2	    3  
        // zeropage,X	SBC oper,X	F5	    2	    4  
        // absolute	    SBC oper	ED	    3	    4  
        // absolute,X	SBC oper,X	FD	    3	    4* 
        // absolute,Y	SBC oper,Y	F9	    3	    4* 
        // (indirect,X)	SBC (oper,X)	E1	2	    6  
        // (indirect),Y	SBC (oper),Y	F1	2	    5* 
        void SBC();

        // Set Carry Flag
        // 1 -> C
        // N Z C I D V
        // - - 1 - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    SEC	        38	    1	    2  
        void SEC();

        // Set Decimal Flag
        // 1 -> D
        // N Z C I D V
        // - - - - 1 -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    SED	        F8	    1	    2  
        void SED();

        // Set Interrupt Disable Status
        // 1 -> I
        // N Z C I D V
        // - - - 1 - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    SEI	        78	    1	    2  
        void SEI();

        // Store Accumulator in Memory
        // A -> M
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	opc	    bytes	cyles
        // zeropage	    STA oper	85	    2	    3  
        // zeropage,X	STA oper,X	95	    2	    4  
        // absolute	    STA oper	8D	    3	    4  
        // absolute,X	STA oper,X	9D	    3	    5  
        // absolute,Y	STA oper,Y	99	    3	    5  
        // (indirect,X)	STA (oper,X)	81	2	    6  
        // (indirect),Y	STA (oper),Y	91	2	    6  
        void STA();

        // Store Index X in Memory
        // X -> M
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	opc	    bytes	cyles
        // zeropage	    STX oper	86	    2	    3  
        // zeropage,Y	STX oper,Y	96	    2	    4  
        // absolute	    STX oper	8E	    3	    4  
        void STX();

        // Store Index Y in Memory
        // Y -> M
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	opc	    bytes	cyles
        // zeropage	    STY oper	84	    2	    3  
        // zeropage,X	STY oper,X	94	    2	    4  
        // absolute	    STY oper	8C	    3	    4  
        void STY();
        
        // Transfer Accumulator to Index X
        // A -> X
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    TAX	        AA	    1	    2  
        void TAX();

        // Transfer Accumulator to Index Y
        // A -> Y
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    TAY	        A8	    1	    2  
        void TAY();

        // Transfer Stack Pointer to Index X
        // SP -> X
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    TSX	        BA	    1	    2  
        void TSX();

        // Transfer Index X to Accumulator
        // X -> A
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    TXA	        8A	    1	    2  
        void TXA();

        // Transfer Index X to Stack Register

        // X -> SP
        // N Z C I D V
        // - - - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    TXS	        9A	    1	    2  
        void TXS();
        
        // Transfer Index Y to Accumulator
        // Y -> A
        // N Z C I D V
        // + + - - - -
        // addressing	assembler	opc	    bytes	cyles
        // implied	    TYA	        98	    1	    2  
        void TYA();
        void IXX();
// * add 1 to cycles if page boundery is crossed

// ** add 1 to cycles if branch occurs on same page
// ** add 2 to cycles if branch occurs to different page
};
