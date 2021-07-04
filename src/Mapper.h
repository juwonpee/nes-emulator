#include "types.h"
#include <vector>
#include <Mapper/Mapper000.h>

using namespace std;

class Mapper {
    public:
        Mapper();
        ~Mapper();
        void init(
            int mapperType, 
            uint8_t PRGROM, 
            uint8_t CHRROM, 
            vector<uint8_t> trainerData, 
            vector<uint8_t> PRGROMData, 
            vector<uint8_t> CHRROMData
        );

        uint8_t (*CPUread)(uint16_t address);
        void (*CPUwrite)(uint16_t address, uint8_t write);
        uint8_t (*PPUread)(uint16_t address);
        void (*PPUwrite)(uint16_t address, uint8_t write);
    private:
        int mapper;

        

};