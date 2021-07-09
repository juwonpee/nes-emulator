// https://wiki.nesdev.com/w/index.php/INES_Mapper_180

#include <vector>
#include <string>

#include "types.h"

using namespace std;

class Mapper094 {
    public:
        Mapper094(
            mirrorType _mirror,
            vector<uint8_t> PRGROMData
        );
        ~Mapper094();

        uint8_t CPUread(uint16_t address);
        void CPUwrite(uint16_t address, uint8_t write);
        uint8_t PPUread(uint16_t address);
        void PPUwrite(uint16_t address, uint8_t write);

        string ROMName = "HVC-UN1ROM";
    private:
        mirrorType mirror;
        uint8_t PRGROMMapNumber = 94;
        uint8_t PRGROMSize = 8;
        uint8_t CHRRAMSize = 1;
        vector<uint8_t> PRGROM, CHRRAM;
        int PRGROMLastBankIndex;
};