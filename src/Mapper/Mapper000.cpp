#include <types.h>
#include <vector>


enum memoryType{
    _PRGROM,
    _PRGRAM,
    _CHRROM,
};


class Mapper000 {
    
    public:
        Mapper000();

        void resize(memoryType _memoryType, int banks, int size) {
            switch (_memoryType) {
                case _PRGROM:
                    // TODO ***TEMPORARY FILLER***
                    _memoryType = _PRGRAM;
            };
        };

        uint8_t CPUread(uint16_t address) {

        };

        void CPUwrite(uint16_t address, uint8_t data) {

        };

        uint8_t PPUread(uint16_t address) {

        };

        void PPUwrite(uint16_t address, uint8_t data) {

        };
    
    private:
        std::vector<uint8_t> PRGROM;
        std::vector<uint8_t> PRGRAM;
        std::vector<uint8_t> CHRROM;
};