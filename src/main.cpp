#include <types.h>
#include <thread>                           // thread class
#include <unistd.h>                         // getopt function
#include <string>                           // string class
#include <iostream>                         // cout function
#include <stdlib.h>                         // exit function
#include <queue>                            // queue class

#include "BUS.h"
#if __linux__
    #include "linux/GUI.h"
#elif _WIN64
    #include "win/GUI.h"
#endif

graphics *graphicsQueue, _graphicsQueue;
input *inputQueue, _inputQueue;
// TODO: struct for sound


using namespace std;

void cmdHelp() {
    cout << "help" << endl;
}

void emulationThread(string directory) {
    BUS emulator(directory, graphicsQueue, inputQueue);
    while(1) {

    }
}

void graphicsThread() {

}

void soundThread() {

}


int main(int argc, char* argv[]) {
    string directory;
    int opt;

    while ((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
            case 'd':
                directory = optarg;
            default:
                cmdHelp();
                exit(EXIT_FAILURE);
        }
    }

    graphicsQueue = &_graphicsQueue;
    inputQueue = &_inputQueue;
    graphicsQueue -> lock.unlock();
    graphicsQueue -> lock.unlock();

    thread NES(emulationThread, directory);
    // TODO: Graphics thread
    // TODO: APU thread
}