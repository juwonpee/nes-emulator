#ifndef BUS_H
#define BUS_H
#include <string>

#include "types.h"
#include "CPU.h"
#include "Cart.h"
#include "RAM.h"

using namespace std;


class BUS {
    public:
        BUS(string _PRGROMdirectory, string _PRGRAMdirectory, graphics* _graphics, input* _input);
        ~BUS();


        uint8_t CPUread(uint16_t _address);
        void CPUwrite(uint16_t _address, uint8_t _data);

        void write(pixel _pixel);
        
        // debug functions
        uint64_t clocks = 0;
        void clockTicks(uint64_t _clocks);
    private:
        graphics* graphicsQueue;
        input* inputQueue;


        uint16_t address;
        uint8_t data;

        string PRGROMdirectory;
        string PRGRAMdirectory;
        CPU* nesCPU;
        Cart* nesCartridge;
        RAM* ram;

        void clock();



    
};

#endif