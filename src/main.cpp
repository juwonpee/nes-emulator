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
bool cpuDebugMode = false;
    


void cmdHelp() {
    cout << "NES emulator, source: https://github.com/juwonpee/NES-emulator" << endl;
    cout << "Parameters:" << endl;
    cout << "-r <Directory of NES ROM>(REQUIRED PARAMETER) ROM directory parameter" << endl;
    cout << "-s <Directory of NES save game> Save game directory parameter" << endl;
    cout << "-d Debug mode, manually increment clock ticks" << endl;
    cout << "-c CPU only debug mode, manually increment clock ticks" << endl;
}

void emulationThread() {
    cout << "In emulation Thread" << endl;
    BUS emulator(PRGROMdirectory, PRGRAMdirectory, &graphics, &input);
    if (debugMode || cpuDebugMode) {
        while(1) {
            emulator.dumpCPU();
            cout << "Enter number of clocks to execute" << endl;
            int clocks;
            cin >> clocks;
            cout << "Executing " << clocks << " clocks" << endl;
            emulator.clock(clocks);
        }
    }
    else {
        emulator.clock(0);
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
    while ((opt = getopt(argc, argv, "r:s:dc")) != -1) {
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
                debugMode = true;
                continue;
            case 'c':
                cout << "Launching in CPU only debug mode" << endl;
                cpuDebugMode = true;
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

    thread* emul = new thread(emulationThread);
    thread* graph;
    thread* sound;
    if (!cpuDebugMode) {
        graph = new thread(graphicsThread);
        sound = new thread(soundThread);
    }
    // TODO: APU thread

    emul -> join();
    cout << "emulation thread joined" << endl;
    if (!cpuDebugMode) {
        graph -> join();
        cout << "graphics thread joined" << endl;
        sound ->join();
        cout << "sound thread joined" << endl;
    }
    
    cout << "graceful exit" << endl;
    return 0;
}