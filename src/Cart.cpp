#include <Cart.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

Cart::Cart(string directory) {
    
    iNES.open(directory, ios::binary);
    if (iNES.fail()) {
        cout << "File does not exist" << endl;
        exit(EXIT_FAILURE);
    }
    


    buffer = new vector<uint8_t>(istreambuf_iterator<char>(iNES), {});
    
    
    // Check whether iNES file format is valid
    if ((*buffer)[0] == 'N' & (*buffer)[1] == 'E' & (*buffer)[2] == 'S' & (*buffer)[3] == 0x1A) {
        // Check header
        PRGROM = (*buffer)[4];
        CRGROM = (*buffer)[5];
        FLAGS6.input = (*buffer)[6];
        FLAGS7.input = (*buffer)[7];
        MAPPER.input = (*buffer)[8];
        ROMSIZE.input = (*buffer)[9];
        EEPROMSIZE.input = (*buffer)[10];
        RAMSIZE.input = (*buffer)[11];
        TIMING.input = (*buffer)[12];
        TYPE.input = (*buffer)[13];

    }
    else {
        cout << "Invalid cartridge format" << endl;
        exit(EXIT_FAILURE);

    }
}

Cart::~Cart() {
    
}