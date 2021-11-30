#pragma once

#include <cstdint>
#include <mutex>
#include <queue>
#include <string>

using namespace std;

typedef struct {
    int x;
    int y;
    int r, g, b;
} pixel_t;
typedef struct {
    queue<pixel_t> pixelQueue;
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
    uint8_t instructionClocks;
    addressingMode addressMode;
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t SP;
    SR_t SR;
    uint16_t PC;
} CPUstatus;

