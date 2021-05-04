#include <string>
#include <vector>
#include "types.h"

class CPU {
    public:
        CPU();
        ~CPU();
        void connectToBus (void* BUS); // Connect to the bus to access its functions
        void clock(); // Run one clock

    private:
        uint8_t A, X, Y, SP;
        uint16_t PC;
        struct STATUS {
            uint8_t C:1; // Carry
            uint8_t Z:1; // Zero
            uint8_t I:1; // Interrupt disable
            uint8_t D:1; // Decimal mode
            uint8_t B:1; // Break
            uint8_t ignore:1; // ignored
            uint8_t V:1; // Overflow
            uint8_t N:1; // Negative
        } SR;
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t data);


        // Helper variables
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
            //                             0xXX01                         0xXX02                         0xXX03                         0xXX04                         0xXX05                         0xXX06                         0xXX07                         0xXX08                         0xXX09                         0xXX0a                         0xXX0b                         0xXX0c                         0xXX0d                         0xXX0e                         0xXX0f
            {"BRK", &CPU::IMP, &CPU::BRK}, {"ORA", &CPU::XIN, &CPU::ORA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"ORA", &CPU::ZPG, &CPU::ORA}, {"ASL", &CPU::ZPG, &CPU::ASL}, {"XXX", &CPU::AXX, &CPU::IXX}, {"PHP", &CPU::IMP, &CPU::PHP}, {"ORA", &CPU::IMM, &CPU::ORA}, {"ASL", &CPU::ACC, &CPU::ASL}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"ORA", &CPU::ABS, &CPU::ORA}, {"ASL", &CPU::ABS, &CPU::ASL}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BPL", &CPU::REL, &CPU::BPL}, {"ORA", &CPU::YIN, &CPU::ORA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"ORA", &CPU::ZPX, &CPU::ORA}, {"ASL", &CPU::ZPX, &CPU::ASL}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CLC", &CPU::IMP, &CPU::CLC}, {"ORA", &CPU::ABY, &CPU::ORA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"ORA", &CPU::ABX, &CPU::ORA}, {"ASL", &CPU::ABX, &CPU::ASL}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"JSR", &CPU::REL, &CPU::JSR}, {"AND", &CPU::XIN, &CPU::AND}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"BIT", &CPU::ZPG, &CPU::BIT}, {"AND", &CPU::ZPG, &CPU::AND}, {"ROL", &CPU::ZPG, &CPU::ROL}, {"XXX", &CPU::AXX, &CPU::IXX}, {"PLP", &CPU::IMP, &CPU::PLP}, {"AND", &CPU::IMM, &CPU::AND}, {"ROL", &CPU::ACC, &CPU::ROL}, {"XXX", &CPU::AXX, &CPU::IXX}, {"BIT", &CPU::ABS, &CPU::BIT}, {"AND", &CPU::ABX, &CPU::AND}, {"ROL", &CPU::ABX, &CPU::ROL}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BMI", &CPU::REL, &CPU::BMI}, {"AND", &CPU::YIN, &CPU::AND}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"AND", &CPU::ZPX, &CPU::AND}, {"ROL", &CPU::ZPG, &CPU::ROL}, {"XXX", &CPU::AXX, &CPU::IXX}, {"SEC", &CPU::IMP, &CPU::SEC}, {"AND", &CPU::ABY, &CPU::AND}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"AND", &CPU::ABX, &CPU::AND}, {"ROL", &CPU::ABX, &CPU::ROL}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"RTI", &CPU::IMP, &CPU::RTI}, {"EOR", &CPU::XIN, &CPU::EOR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"EOR", &CPU::ZPG, &CPU::EOR}, {"LSR", &CPU::ZPG, &CPU::LSR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"PHA", &CPU::IMP, &CPU::PHA}, {"EOR", &CPU::IMM, &CPU::EOR}, {"LSR", &CPU::ACC, &CPU::LSR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"JMP", &CPU::ABS, &CPU::JMP}, {"EOR", &CPU::ABS, &CPU::EOR}, {"LSR", &CPU::ABS, &CPU::LSR}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BVC", &CPU::REL, &CPU::BVC}, {"EOR", &CPU::XIN, &CPU::EOR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"EOR", &CPU::ZPX, &CPU::EOR}, {"LSR", &CPU::ZPX, &CPU::LSR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CLI", &CPU::IMP, &CPU::CLI}, {"EOR", &CPU::ABY, &CPU::EOR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"EOR", &CPU::ABX, &CPU::EOR}, {"LSR", &CPU::ABX, &CPU::LSR}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"RTS", &CPU::IMP, &CPU::RTS}, {"ADC", &CPU::XIN, &CPU::ADC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"ADC", &CPU::ZPG, &CPU::ADC}, {"ROR", &CPU::ZPG, &CPU::ROR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"PLA", &CPU::IMP, &CPU::PLA}, {"ADC", &CPU::IMM, &CPU::ADC}, {"ROR", &CPU::ACC, &CPU::ROR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"JMP", &CPU::IND, &CPU::JMP}, {"ADC", &CPU::ABS, &CPU::ADC}, {"ROR", &CPU::ABS, &CPU::ROR}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BVS", &CPU::REL, &CPU::BVS}, {"ADC", &CPU::YIN, &CPU::ADC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"ADC", &CPU::ZPX, &CPU::ADC}, {"ROR", &CPU::ZPX, &CPU::ROR}, {"XXX", &CPU::AXX, &CPU::IXX}, {"SEI", &CPU::IMP, &CPU::SEI}, {"ADC", &CPU::ABY, &CPU::ADC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"ADC", &CPU::ABX, &CPU::ADC}, {"ROR", &CPU::ABX, &CPU::ROR}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"XXX", &CPU::AXX, &CPU::IXX}, {"STA", &CPU::XIN, &CPU::STA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"STY", &CPU::ZPG, &CPU::STY}, {"STA", &CPU::ZPG, &CPU::STA}, {"STX", &CPU::ZPG, &CPU::STX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"DEY", &CPU::IMP, &CPU::DEY}, {"XXX", &CPU::AXX, &CPU::IXX}, {"TXA", &CPU::IMP, &CPU::TXA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"STY", &CPU::ABS, &CPU::STY}, {"STA", &CPU::ABS, &CPU::STA}, {"STX", &CPU::ABS, &CPU::STX}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BCC", &CPU::REL, &CPU::BCC}, {"STA", &CPU::YIN, &CPU::STA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"STY", &CPU::ZPX, &CPU::STY}, {"STA", &CPU::ZPX, &CPU::STA}, {"STX", &CPU::ZPX, &CPU::STX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"TYA", &CPU::IMP, &CPU::TYA}, {"STA", &CPU::ABY, &CPU::STA}, {"TXS", &CPU::IMP, &CPU::TXS}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"STA", &CPU::ABX, &CPU::STA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"LDY", &CPU::IMM, &CPU::LDY}, {"LDA", &CPU::YIN, &CPU::LDA}, {"LDX", &CPU::IMM, &CPU::LDX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"LDY", &CPU::ZPG, &CPU::LDY}, {"LDA", &CPU::ZPG, &CPU::LDA}, {"LDX", &CPU::ZPG, &CPU::LDX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"TAY", &CPU::IMP, &CPU::TAY}, {"LDA", &CPU::IMM, &CPU::LDA}, {"TAX", &CPU::IMP, &CPU::TAX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"LDY", &CPU::ABS, &CPU::LDY}, {"LDA", &CPU::ABS, &CPU::LDA}, {"LDX", &CPU::ABS, &CPU::LDX}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BCS", &CPU::REL, &CPU::BCS}, {"LDA", &CPU::YIN, &CPU::LDA}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"LDY", &CPU::ZPX, &CPU::LDY}, {"LDA", &CPU::ZPX, &CPU::LDA}, {"LDX", &CPU::ZPX, &CPU::LDX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CLV", &CPU::IMP, &CPU::CLV}, {"LDA", &CPU::ABY, &CPU::LDA}, {"TSX", &CPU::IMP, &CPU::TSX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"LDY", &CPU::ABX, &CPU::LDY}, {"LDA", &CPU::ABX, &CPU::LDA}, {"LDX", &CPU::ABX, &CPU::LDX}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"CPY", &CPU::REL, &CPU::CPY}, {"CMP", &CPU::XIN, &CPU::CMP}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CPY", &CPU::ZPG, &CPU::CPY}, {"CMP", &CPU::ZPG, &CPU::CMP}, {"DEC", &CPU::ZPG, &CPU::DEC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"INY", &CPU::IMP, &CPU::INY}, {"CMP", &CPU::IMM, &CPU::CMP}, {"DEX", &CPU::IMP, &CPU::DEX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CPY", &CPU::ABS, &CPU::CPY}, {"CMP", &CPU::ABS, &CPU::CMP}, {"DEC", &CPU::ABS, &CPU::DEC}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BNE", &CPU::REL, &CPU::BNE}, {"CMP", &CPU::XIN, &CPU::CMP}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CMP", &CPU::ZPX, &CPU::CMP}, {"DEC", &CPU::ZPX, &CPU::DEC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CLD", &CPU::IMP, &CPU::CLD}, {"CMP", &CPU::ABY, &CPU::CMP}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CMP", &CPU::ABX, &CPU::CMP}, {"DEC", &CPU::ABX, &CPU::DEC}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"CPX", &CPU::IMM, &CPU::CPX}, {"SBC", &CPU::XIN, &CPU::SBC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CPX", &CPU::ZPG, &CPU::CPX}, {"SBC", &CPU::ZPG, &CPU::SBC}, {"INC", &CPU::ZPG, &CPU::INC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"INX", &CPU::IMP, &CPU::INX}, {"SBC", &CPU::IMM, &CPU::SBC}, {"NOP", &CPU::IMP, &CPU::NOP}, {"XXX", &CPU::AXX, &CPU::IXX}, {"CPX", &CPU::ABS, &CPU::CPX}, {"SBC", &CPU::ABS, &CPU::SBC}, {"INC", &CPU::ABS, &CPU::INC}, {"XXX", &CPU::AXX, &CPU::IXX}, 
            {"BEQ", &CPU::REL, &CPU::BEQ}, {"SBC", &CPU::YIN, &CPU::SBC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"SBC", &CPU::ZPX, &CPU::SBC}, {"INC", &CPU::ZPX, &CPU::INC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"SED", &CPU::IMP, &CPU::SED}, {"SBC", &CPU::ABY, &CPU::SBC}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"XXX", &CPU::AXX, &CPU::IXX}, {"SBC", &CPU::ABX, &CPU::SBC}, {"INC", &CPU::ABX, &CPU::INC}, {"XXX", &CPU::AXX, &CPU::IXX}, 
        };
        
        // Addressing modes
        enum addressingMode {
            acc, abs, abx, aby, imm, imp, ind, xin, yin, rel, zpg, zpx, zpy, axx
        } addressMode;
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

        
        void CLC();
        void CLD();
        void CLI();
        void CLV();
        void CMP();
        void CPX();
        void CPY();
        void DEC();
        void DEX();
        void DEY();
        void EOR();
        void INC();
        void INX();
        void INY();
        void JMP();
        void JSR();
        void LDA();
        void LDX();
        void LDY();
        void LSR();
        void NOP();
        void ORA();
        void PHA();
        void PHP();
        void PLA();
        void PLP();
        void ROL();
        void ROR();
        void RTI();
        void RTS();
        void SBC();
        void SEC();
        void SED();
        void SEI();
        void STA();
        void STX();
        void STY();
        void TAX();
        void TAY();
        void TSX();
        void TXA();
        void TXS();
        void TYA();
        void IXX();
};