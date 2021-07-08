// https://wiki.nesdev.com/w/index.php/INES_Mapper_180

#include <vector>
#include <string>

#include "types.h"

using namespace std;

class Mapper180 {
    public:
        Mapper180(
            mirrorType _mirror,
            vector<uint8_t> PRGROMData
        );
        ~Mapper180();

        uint8_t CPUread(uint16_t address);
        void CPUwrite(uint16_t address, uint8_t write);
        uint8_t PPUread(uint16_t address);
        void PPUwrite(uint16_t address, uint8_t write);

        string ROMName = "UNROM";
    private:
        uint8_t PRGROMMapNumber = 180;
        uint8_t PRGROMSize = 8;
        uint8_t CHRRAMSize = 1;
        vector<uint8_t> PRGROM, CHRRAM;
};