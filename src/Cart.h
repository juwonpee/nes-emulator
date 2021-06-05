#include <types.h>
#include <fstream>
#include <string>
#include <vector>

class Cart {
    public:
        std::ifstream iNES;

        Cart(std::string directory);
        ~Cart();

        uint8_t get(uint16_t address);
        void set(uint16_t address, uint8_t data);

    private:
        std::vector<uint8_t> buffer;

        void init();
        


};