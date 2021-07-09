#include <thread>                           // thread class
#include <unistd.h>                         // getopt function
#include <string>                           // string class
#include <iostream>                         // cout function
#include <stdlib.h>                         // exit function

#include "types.h"
#include "BUS.h"
#include "GUI.h"


using namespace std;

graphics_t graphics;
input_t input;
// TODO sound struct
string PRGROMdirectory;
string PRGRAMdirectory;
bool debugMode = false;
    


void cmdHelp() {
    cout << "NES emulator, source: github.com/juwonpee/NES-emulator" << endl;
    cout << "Parameters:" << endl;
    cout << "-r <Directory of NES ROM>(REQUIRED PARAMETER) " << endl << "ROM directory parameter" << endl;
    cout << "-s <Directory of NES save game " << endl << "Save game directory parameter" << endl;
    cout << "-d " << endl << "Debug mode, manually increment clock ticks" << endl;
}

void emulationThread() {
    cout << "In emulation Thread" << endl;
    BUS emulator(PRGROMdirectory, PRGRAMdirectory, &graphics, &input);
    if (debugMode == false) {
        emulator.clock(0);
    }
    else {
        while(1) {
            int clocks;
            cin >> clocks;
            emulator.clock(clocks);
        }
    }

}

void graphicsThread() {
    cout << "In graphics thread" << endl;
    GUI gameWindow;
}

void soundThread() {
    cout << "In sound thread" << endl;
}


int main(int argc, char* argv[]) {

    cout << "main thread" << endl;

    int opt;
    while ((opt = getopt(argc, argv, "r:s:d")) != -1) {
        switch (opt) {
            case 'r':
                PRGROMdirectory = optarg;
                cout << "Game ROM directory: " << PRGROMdirectory << endl;
                continue;
            case 's':
                cout << "Save game directory: " << PRGRAMdirectory << endl;
                PRGRAMdirectory = optarg;
                continue;
            case 'd':
                cout << "Launching in debug mode" << endl;
                continue;

        }
    }
    if (PRGROMdirectory == "") {
        cmdHelp();
        exit(EXIT_FAILURE);
    }

    // sanity unlocking
    graphics.lock.unlock();
    input.lock.unlock();

    thread graph(graphicsThread);
    thread emul(emulationThread);
    thread sound(soundThread);
    // TODO: APU thread

    graph.join();
    cout << "graphics thread joined" << endl;
    emul.join();
    cout << "emulation thread joined" << endl;
    sound.join();
    cout << "sound thread joined" << endl;
    
    cout << "graceful exit" << endl;
    return 0;
}