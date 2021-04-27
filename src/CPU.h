#include <types.h>

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
            uint8_t O:1; // Overflow
            uint8_t N:1; // Negative
        } ST;

        // Helper variables
        lookup = {//                0xXX01                  0xXX02                  0xXX03                  0xXX04                  0xXX05                  0xXX06                  0xXX07                 0xXX08                   0xXX09                  0xXX0a                  0xXX0b                  0xXX0c                  0xXX0d                  0xXX0e                  0xXX0f
            {"BRK", &IMP, &BRK, 7}, {"ORA", &INX, &ORA, 7}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"ORA", &ZPG, &ORA, 3}, {"ASL", &ZPG, &ASL, 5}, {"XXX", &AXX, &IXX, 1}, {"PHP", &IMP, &PHP, 3}, {"ORA", &IMM, &ORA ,2}, {"ASL", &ACC, &ASL ,2}, {"XXX", &AXX, &IXX ,1}, {"XXX", &AXX, &IXX ,1}, {"ORA", &ABS, &ORA ,4}, {"ASL", &ABS, &ASL ,2}, {"XXX", &AXX, &IXX ,1}, 
            {"BPL", &REL, &BPL, 2}, {"ORA", &INY, &ORA, 5}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"ORA", &ZPX, &ORA, 4}, {"ASL", &ZPX, &ASL, 6}, {"XXX", &AXX, &IXX, 1}, {"CLC", &IMP, &CLC, 2}, {"ORA", &ABY, &ORA, 4}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"ORA", &ABX, &ORA, 4}, {"ASL", &ABX, &ASL, 7}, {"XXX", &AXX, &IXX, 1}, 
            {"JSR", &REL, &JSR, 6}, {"AND", &INX, &AND, 6}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"BIT", &ZPG, &BIT, 3}, {"AND", &ZPG, &AND, 3}, {"ROL", &ZPG, &ROL, 5}, {"XXX", &AXX, &IXX, 1}, {"PLP", &IMP, &PLP, 4}, {"AND", &IMM, &AND, 2}, {"ROL", &ACC, &ROL, 2}, {"XXX", &AXX, &IXX, 1}, {"BIT", &ABS, &BIT, 4}, {"AND", &ABX, &AND, 4}, {"ROL", &ABX, &ROL, 6}, {"XXX", &AXX, &IXX, 1}, 
            {"BMI", &REL, &BMI, 2}, {"AND", &INY, &AND, 5}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"AND", &ZPX, &AND, 4}, {"ROL", &ZPG, &ROL, 6}, {"XXX", &AXX, &IXX, 1}, {"SEC", &IMP, &SEC, 2}, {"AND", &ABY, &AND, 4}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"AND", &ABX, &AND, 4}, {"ROL", &ABX, &ROL, 7}, {"XXX", &AXX, &IXX, 1}, 
            {"RTI", &IMP, &RTI, 6}, {"EOR", &INX, &EOR, 6}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"XXX", &AXX, &IXX, 1}, {"EOR", &ZPG, &EOR, 3}, {"LSR", &ZPG, &LSR, 5}, {"XXX", &AXX, &IXX, 1}, {"PHA", &IMP, &PHA, 3}, {"EOR", &IMM, &EOR, 2}, {"LSR", &ACC, &LSR, 2}, {"XXX", &AXX, &IXX, 1}, {"JMP", &ABS, &JMP, 3}, {"EOR", &ABS, &EOR, 4}, {"LSR", &ABS, &LSR, 6}, {"XXX", &AXX, &IXX, 1}, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
            {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, {"", &, &, }, 
        };
        
		// { "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		// { "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		// { "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		// { "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		// { "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		// { "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		// { "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		// { "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		// { "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		// { "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		// { "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		// { "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },

        // Addressing modes
        enum addressingMode {
            ACC, ABS, ABX, ABY, IMM, IMP, IND, INX, INY, REL, ZPG, ZPY
        } addressMode;
        void ACC();
        void ABS();
        void ABX();
        void ABY();
        void IMM();
        void IMP();
        void IND();
        void INX();
        void INY();
        void REL();
        void ZPG();
        void ZPX();
        void ZPY();
        void AXX();

        // Instructions
        void ADC();
        void AND();
        void ASL();
        void BCC();
        void BCS();
        void BEQ();
        void BIT();
        void BMI();
        void BNE();
        void BPL();
        void BRK();
        void BVC();
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
        void EOR();
        void INC();
        void INX();
        void INX();
        void INY();
        void JMP();
        void JSR();
        void LDA();
        void LDX();
        void LDY();
        void LSR();
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