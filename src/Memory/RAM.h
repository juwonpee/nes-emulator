#include <vector>

#include "types.h"

using namespace std;

class RAM {
    public:
        RAM();
        ~RAM();

        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t data);

    private:
        uint8_t data[2048];
};