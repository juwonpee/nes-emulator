#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <mutex>
#include <queue>

typedef struct {
    int x;
    int y;
    int r, g, b;
} pixel;
typedef struct {
    std::queue<pixel> pixelQueue;
    std::mutex lock;
} graphics;

typedef struct {
    bool up, down, left, right, select, start, a, b;
} inputFrame;
typedef struct {
    std::queue<inputFrame> inputQueue;
    std::mutex lock;
} input;

// TODO: struct for sound

#endif