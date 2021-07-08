#include "types.h"
#include "RAM.h"

RAM::RAM() {

}

RAM::~RAM() {

}

uint8_t RAM::read(uint16_t address) {
    return data[address];
}

void RAM::write(uint16_t address, uint8_t _data) {
    data[address] = _data;
}