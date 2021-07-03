#include <types.h>
#include <thread>                           // thread class
#include <unistd.h>                         // getopt function
#include <string>                           // string class
#include <iostream>                         // cout function
#include <stdlib.h>                         // exit function

#include "BUS.h"


graphics _graphics;
input _input;
// TODO sound struct
std::string directory;
    


void cmdHelp() {
    std::cout << "help" << std::endl;
}

void emulationThread() {
    std::cout << "In emulation Thread" << std::endl;
    BUS emulator(directory, &_graphics, &_input);
    while(1) {

    }
}

void graphicsThread() {

}

void soundThread() {

}


int main(int argc, char* argv[]) {
    std::cout << "main thread" << std::endl;

    int opt;

    while ((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
            case 'd':
                std::cout << directory << std::endl;
                directory = optarg;
        }
    }
    if (directory == "") {
        cmdHelp();
        exit(EXIT_FAILURE);
    }

    // sanity unlocking
    _graphics.lock.unlock();
    _input.lock.unlock();

    std::thread emul(emulationThread);
    std::thread graph(graphicsThread);
    std::thread sound(soundThread);
    // TODO: APU thread
    emul.join();
    graph.join();
    sound.join();
}