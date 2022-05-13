#include "graphicsEngine.h"

using namespace sf;
using namespace std;

namespace GraphicsEngine {
	graphicsEngine::graphicsEngine(int _width, int _height, dataShare_t* _dataShare, string name) {
		width = _width;
		height = _height;
		dataShare = _dataShare;

		window = new RenderWindow(VideoMode(width, height), name);
		texture.create(width, height);
        sprite.setTexture(texture);
		frame = (uint8_t*)malloc(width * height * 4);

        update();
	}

	graphicsEngine::~graphicsEngine() {
        window->close();
        free(window);
        free(frame);
	}

	void graphicsEngine::update() {
        time_t start = time (NULL);
        
        uint64_t frames = 0;
        while (1) {
            // Check fps
            time_t now = time (NULL);

            // Mutex lock to prevent concurrent access between graphics and emulation thread.
            dataShare->lock.lock();
            while (!dataShare->pixels.empty()) {
                pixel_t pixel = dataShare->pixels.front();
                dataShare->pixels.pop();
                frame[updateCount * 4] = pixel.r;
                frame[updateCount * 4 + 1] = pixel.g;
                frame[updateCount * 4 + 2] = pixel.b;
                frame[updateCount * 4 + 3] = pixel.a;
                updateCount++;
                // Reset updateCount if it has reached the end of the frame
                if (updateCount == width * height) updateCount = 0;
            }
            // Mutex unlock as it has emptied the queue.
            dataShare->lock.unlock();

            texture.update(frame);
            sprite.setTexture(texture);

            // Drawing time
            window->clear(Color::Black);
            window->draw(sprite);
            window->display();  // Finished frame

            // End time
            if (now > start) {
                cout << "fps:" <<frames << endl;
                start = now;
                frames = 0;
                frames++;
            }
            else {
                frames++;
            }
        }

	}
	
}