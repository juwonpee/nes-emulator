#include <types.h>
#include <fstream>
#include <string>
#include <vector>
#include <Mapper.h>

using namespace std;

class Cart {
    public:

        Cart(string directory);
        ~Cart();

        uint8_t cpuRead(uint16_t address);
        void cpuWrite(uint16_t address, uint8_t data);

    private:
        uint8_t PRGROM;
        uint8_t CHRROM;

        // D~7654 3210
        // ---------
        // NNNN FTBM
        // |||| |||+-- Hard-wired nametable mirroring type
        // |||| |||     0: Horizontal or mapper-controlled
        // |||| |||     1: Vertical
        // |||| ||+--- "Battery" and other non-volatile memory
        // |||| ||      0: Not present
        // |||| ||      1: Present
        // |||| |+--- 512-byte Trainer
        // |||| |      0: Not present
        // |||| |      1: Present between Header and PRG-ROM data
        // |||| +---- Hard-wired four-screen mode
        // ||||        0: No
        // ||||        1: Yes
        // ++++------ Mapper Number D0..D3
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t M:1;
                    uint8_t B:1;
                    uint8_t T:1;
                    uint8_t F:1;
                    uint8_t N:4;
                };
            };
        } FLAGS6;

        // D~7654 3210
        // ---------
        // NNNN 10TT
        // |||| ||++- Console type
        // |||| ||     0: Nintendo Entertainment System/Family Computer
        // |||| ||     1: Nintendo Vs. System
        // |||| ||     2: Nintendo Playchoice 10
        // |||| ||     3: Extended Console Type
        // |||| ++--- NES 2.0 identifier
        // ++++------ Mapper Number D4..D7
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t T:2;
                    uint8_t iNES2:2;
                    uint8_t N:4;
                };
            };
        } FLAGS7;

//-------------------iNES1.0 FORMAT------------------------

        // 76543210
        // ||||||||
        // ++++++++- PRG RAM size
        struct {
            union {
                uint8_t input;
                uint8_t PRGRAM;
            };
        } FLAGS8;

        // 76543210
        // ||||||||
        // |||||||+- TV system (0: NTSC; 1: PAL)
        // +++++++-- Reserved, set to zero
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t TYSystem:1;
                    uint8_t reserved:7;
                };
            };
        } FLAGS9;

        // 76543210
        // ||  ||
        // ||  ++- TV system (0: NTSC; 2: PAL; 1/3: dual compatible)
        // |+----- PRG RAM ($6000-$7FFF) (0: present; 1: not present)
        // +------ 0: Board has no bus conflicts; 1: Board has bus conflicts
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t reserved0:2;
                    uint8_t TYSystem:2;
                    uint8_t reserved1:2;
                    uint8_t PRGRAMPresent:1;
                    uint8_t BUSConflicts:1;
                };
            };
        } FLAGS10;

//-------------------iNES2.0 FORMAT------------------------

        // D~7654 3210
        // ---------
        // SSSS NNNN
        // |||| ++++- Mapper number D8..D11
        // ++++------ Submapper number
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t N:4;
                    uint8_t C:4;       
                };
            };
        } MAPPER;

        // D~7654 3210
        // ---------
        // CCCC PPPP
        // |||| ++++- PRG-ROM size MSB
        // ++++------ CHR-ROM size MSB
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t P:4;
                    uint8_t C:4;
                };
            };
        } ROMSIZE;

        // D~7654 3210
        // ---------
        // pppp PPPP
        // |||| ++++- PRG-RAM (volatile) shift count
        // ++++------ PRG-NVRAM/EEPROM (non-volatile) shift count
        // If the shift count is zero, there is no PRG-(NV)RAM.
        // If the shift count is non-zero, the actual size is
        // "64 << shift count" bytes, i.e. 8192 bytes for a shift count of 7.
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t PV:4;
                    uint8_t PN:4;
                };
            };
        } EEPROMSIZE;

        // D~7654 3210
        // ---------
        // cccc CCCC
        // |||| ++++- CHR-RAM size (volatile) shift count
        // ++++------ CHR-NVRAM size (non-volatile) shift count
        // If the shift count is zero, there is no CHR-(NV)RAM.
        // If the shift count is non-zero, the actual size is
        // "64 << shift count" bytes, i.e. 8192 bytes for a shift count of 7.
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t CV:4;
                    uint8_t CN:4;
                };
            };
        } RAMSIZE;

        // D~7654 3210
        // ---------
        // .... ..VV
        //        ++- CPU/PPU timing mode
        //             0: RP2C02 ("NTSC NES")
        //             1: RP2C07 ("Licensed PAL NES")
        //             2: Multiple-region
        //             3: UMC 6527P ("Dendy")
        struct {
            union {
                uint8_t input;
                struct {
                    uint8_t V:2;
                };
            };
        } TIMING;

        // D~7654 3210
        // ---------
        // MMMM PPPP
        // |||| ++++- Vs. PPU Type
        // ++++------ Vs. Hardware Type
        struct {
            union{
                uint8_t input;
                struct{
                    uint8_t P:4;
                    uint8_t M:4;
                };
            };
        } TYPE;

        ifstream iNES;
        vector<uint8_t>* buffer;
        vector<uint8_t> trainer;
        vector<uint8_t> bufferPRGROM;
        vector<uint8_t> bufferCHRROM;

        Mapper mapper;

        void iNES1();
        void iNES2();



};