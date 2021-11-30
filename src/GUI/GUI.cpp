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

#include <iostream>

#include "GUI.h"

using namespace std;
using namespace sf;

GUI::GUI() {
    cout << "In GUI class" << endl;
    window = new RenderWindow(VideoMode(800, 600), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window -> isOpen())
    {
        cout << "Window refresh" << endl;
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
GUI::~GUI() {
    delete window;
}