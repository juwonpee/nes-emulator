#include <vector>
#include "Mapper.h"

Mapper::Mapper() {
}

Mapper::~Mapper() {
}

void Mapper::init(
    int mapperType, 
    uint8_t PRGROM,
    uint8_t CHRROM, 
    vector<uint8_t> trainerData, 
    vector<uint8_t> PRGROMData, 
    vector<uint8_t> CHRROMData
)
{
    switch (mapperType) {
        case 0:
            Mapper000 mapper(PRGROM, CHRROM, PRGROMData, CHRROMData);
            
    }
}