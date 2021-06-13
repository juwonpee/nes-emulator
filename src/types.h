#include <cstdint>
#include <queue>
#include <mutex>

using namespace std;

struct pixel {
    int x;
    int y;
    int r, g, b;
};
struct graphics{
    queue<pixel> graphicsQueue;
    mutex lock;
};

struct inputFrame {
    bool up, down, left, right, select, start, a, b;
};
struct input{
    queue<inputFrame> inputQueue;
    mutex lock;
};

// TODO: struct for sound