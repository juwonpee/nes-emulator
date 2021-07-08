#include "types.h"
#include <vector>
#include <Mapper/Mapper000.h>
#include <Mapper/Mapper002.h>
#include <Mapper/Mapper094.h>
#include <Mapper/Mapper180.h>


using namespace std;

class Mapper {
    public:
        Mapper(
            int mapperType, 
            uint8_t PRGROM, 
            uint8_t CHRROM, 
            mirrorType _mirror,
            screenType _screen,
            vector<uint8_t> trainerData, 
            vector<uint8_t> PRGROMData, 
            vector<uint8_t> CHRROMData
        );
        ~Mapper();

        uint8_t CPUread(uint16_t address);
        void CPUwrite(uint16_t address, uint8_t write);
        uint8_t PPUread(uint16_t address);
        void PPUwrite(uint16_t address, uint8_t write);
    private:
        int mapper;
        Mapper000* mapper000;
        Mapper002* mapper002;
        Mapper094* mapper094;
        Mapper180* mapper180;
        
};