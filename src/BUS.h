#ifndef BUS_H
#define BUS_H

#include <types.h>
#include <CPU.h>
#include <Cart.h>


class BUS {
    public:
        BUS(std::string _directory, graphics* _graphics, input* _input);
        ~BUS();


        uint8_t read(uint16_t _address);
        void write(uint16_t _address, uint8_t _data);

        void write(pixel _pixel);
        
        // debug functions
        uint64_t clocks = 0;
        void clockTicks(uint64_t _clocks);
    private:
        graphics* graphicsQueue;
        input* inputQueue;


        uint16_t address;
        uint8_t data;

        std::string directory;
        CPU* nesCPU;
        Cart* nesCartridge;

        void clock();



    
};

#endif