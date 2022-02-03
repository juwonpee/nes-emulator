/*
   Copyright [2021] [juwonpee]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

#include <cstdint>
#include <mutex>
#include <queue>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef struct {
    uint8_t r, g, b;
} pixel_colour_t;
typedef struct {
    
    queue<pixel_colour_t> pixelQueue;
    mutex lock;
} graphics_t;

typedef struct {
    bool up, down, left, right, select, start, a, b;
} inputFrame_t;
typedef struct {
    queue<inputFrame_t> inputQueue;
    mutex lock;
} input_t;

// TODO: struct for sound


enum mirrorType {
    horizontal = 0,
    vertical = 1
};
enum screenType {
    single = 0,
    quad = 1
};

// CPU structs
typedef struct {
    union {
        uint8_t byte;
        struct {
            uint8_t C:1; // Carry
            uint8_t Z:1; // Zero
            uint8_t I:1; // Interrupt disable
            uint8_t D:1; // Decimal mode
            uint8_t B:1; // Break
            uint8_t ignore:1; // ignored
            uint8_t V:1; // Overflow
            uint8_t N:1; // Negative
        };
    };
} SR_t;

enum addressingMode {
    acc, abl, abx, aby, imm, imp, ind, xin, yin, rel, zpg, zpx, zpy, axx
} ;

// Structs used for debugging
typedef struct {
    string opcode;
    uint8_t operandLow, operandHigh;
    uint16_t finalData, finalAddress;
    uint8_t instructionClocks;
    addressingMode addressMode;
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t SP;
    SR_t SR;
    uint16_t PC;
} CPUstatus;

