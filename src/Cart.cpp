#include <iostream>
#include <stdlib.h>
#include <algorithm>

#include <Cart.h>

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
        CHRROM = (*buffer)[5];
        FLAGS6.input = (*buffer)[6];
        FLAGS7.input = (*buffer)[7];
        FLAGS8.input = MAPPER.input = (*buffer)[8];
        FLAGS9.input = ROMSIZE.input = (*buffer)[9];
        FLAGS10.input = EEPROMSIZE.input = (*buffer)[10];
        RAMSIZE.input = (*buffer)[11];
        TIMING.input = (*buffer)[12];
        TYPE.input = (*buffer)[13];

    }
    else {
        cout << "Invalid cartridge format" << endl;
        exit(EXIT_FAILURE);
    }

    // Copy data from buffer into mappers
    long bufferPointer = 16;
    if (FLAGS6.T) {
        copy(&(*buffer)[bufferPointer], &(*buffer)[bufferPointer + 512], back_inserter(trainer));
        bufferPointer += 512;
    }
    copy(&(*buffer)[bufferPointer], &(*buffer)[bufferPointer + PRGROM * 16384], back_inserter(bufferPRGROM));
    bufferPointer += PRGROM * 16384;
    copy(&(*buffer)[bufferPointer], &(*buffer)[bufferPointer + CHRROM * 8192], back_inserter(bufferPRGROM));
    

    if (FLAGS7.iNES2 == 0b10) iNES2();
    else iNES1();


}

Cart::~Cart() {
    
}

void Cart::iNES1() {
    cout << "iNES1.0" << endl;
    int mapperNumber = FLAGS6.N + FLAGS7.N << 4;
    mapper.init(mapperNumber, PRGROM, CHRROM, trainer, bufferPRGROM, bufferCHRROM);
}

void Cart::iNES2() {
    cout << "iNES2.0" <<endl;
}