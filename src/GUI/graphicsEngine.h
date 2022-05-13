#pragma once

#include "types.h"
#include <SFML/Graphics.hpp>
#include <mutex>
#include <cstring>
#include <queue>
#include <memory>
#include <vector>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;

namespace GraphicsEngine {

    typedef struct{
        uint8_t r, g, b, a;
    } pixel_t;

    typedef struct{
        mutex lock;
        queue<pixel_t> pixels;    // Pixels are always starting from 0,0 to build a frame
    } dataShare_t;

    class graphicsEngine {
        public:
            graphicsEngine(int _width, int _height, dataShare_t* _dataShare, string name);
            ~graphicsEngine();

            void clear();

        private:
            int width;
            int height;

            dataShare_t* dataShare;
            RenderWindow* window;

            Texture texture;
            Sprite sprite;
            uint8_t* frame;

            // Helper variables
            uint32_t updateCount = 0;

            void update();
    };
}

