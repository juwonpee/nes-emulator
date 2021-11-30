#include <vector>
#include <string>

#include "types.h"

using namespace std;

class Mapper002 {
    public:
        Mapper002(
            mirrorType _mirror,
            vector<uint8_t> PRGROMData
        );
        ~Mapper002();

        uint8_t CPUread(uint16_t address);
        void CPUwrite(uint16_t address, uint8_t write);
        uint8_t PPUread(uint16_t address);
        void PPUwrite(uint16_t address, uint8_t write);

        string ROMName = "UOROM";
    private:
        uint8_t PRGROMMapNumber = 0;
        int PRGROMLastBankPointer;
        uint8_t PRGROMSize;
        vector<uint8_t> PRGROM, CHRRAM;
        mirrorType mirror;
};