#include <GUI.h>

GUI::GUI() {
    window = new sf::RenderWindow(sf::VideoMode(256, 240), "NES-emulator");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window -> isOpen())
    {
        sf::Event event;
        while (window -> pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window -> close();
        }

        window -> clear();
        window -> draw(shape);
        window -> display();
    }
}