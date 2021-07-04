#include <vector>
#include "types.h"

using namespace std;

class Mapper000 {
    public:
        Mapper000(
            uint8_t PRGROMSize, 
            uint8_t CHRROMSize,
            vector<uint8_t> PRGROMData,
            vector<uint8_t> CHRROMData
        );
        ~Mapper000();

        uint8_t CPUread(uint16_t address);
        void CPUwrite(uint16_t address, uint8_t write);
        uint8_t PPUread(uint16_t address);
        void PPUwrite(uint16_t address, uint8_t write);
    private:
        uint8_t PRGSize, CHRSize;
        vector<uint8_t> PRGROM, CHRROM;

        
};