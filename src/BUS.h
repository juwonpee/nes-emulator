#include <types.h>
#include <CPU.h>
#include <Cart.h>


class Bus {
    public:
        Bus(std::string directory);
    private:
        std::string directory;
        CPU nesCPU();
        Cart nesCartridge(std::string directory);



    
};