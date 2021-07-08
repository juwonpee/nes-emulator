#include <thread>                           // thread class
#include <unistd.h>                         // getopt function
#include <string>                           // string class
#include <iostream>                         // cout function
#include <stdlib.h>                         // exit function

#include "types.h"
#include "BUS.h"
#include "GUI.h"


using namespace std;

graphics _graphics;
input _input;
// TODO sound struct
string PRGROMdirectory;
string PRGRAMdirectory;
    


void cmdHelp() {
    cout << "NES emulator, source: github.com/juwonpee/NES-emulator" << endl;
    cout << "Parameters:" << endl;
    cout << "-d <PRGROMdirectory of NES ROM>" << endl;
}

void emulationThread() {
    cout << "In emulation Thread" << endl;
    BUS emulator(PRGROMdirectory, PRGRAMdirectory, &_graphics, &_input);
    while(1) {

    }
}

void graphicsThread() {
    cout << "In graphics thread" << endl;
    GUI window();
    while(1) {

    }

}

void soundThread() {
    cout << "In sound thread" << endl;
    while(1) {

    }
}


int main(int argc, char* argv[]) {
    cout << "main thread" << endl;

    int opt;

    // while ((opt = getopt(argc, argv, "ds:")) != -1) {
    while ((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
            case 'd':
                cout << "Loading game ROM" << endl;
                PRGROMdirectory = optarg;
                break;
            // TODO:implement save game loads
            // case 's':
            //     cout << "loading save game" << endl;
            //     PRGRAMdirectory = optarg;
            //     break;
        }
    }
    if (PRGROMdirectory == "") {
        cmdHelp();
        exit(EXIT_FAILURE);
    }

    // sanity unlocking
    _graphics.lock.unlock();
    _input.lock.unlock();

    thread emul(emulationThread);
    thread graph(graphicsThread);
    thread sound(soundThread);
    // TODO: APU thread
    emul.join();
    cout << "emulation thread joined" << endl;
    graph.join();
    cout << "graphics thread joined" << endl;
    sound.join();
    cout << "sound thread joined" << endl;
    while (1) {
        // do nothing
    }
}