#include <GUI.h>

using namespace std;
using namespace sf;

GUI::GUI() {
    window = new RenderWindow(VideoMode(800, 600), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window -> isOpen())
    {
        Event event;
        while (window -> pollEvent(event))
        {
            if (event.type == Event::Closed)
                window -> close();
        }

        window -> clear();
        window -> draw(shape);
        window -> display();
    }

    return;
}