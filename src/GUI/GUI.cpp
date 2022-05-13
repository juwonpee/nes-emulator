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


#include "GUI.h"

using namespace std;
using namespace GraphicsEngine;

void graphicsThreadFunction(uint64_t length, uint64_t height, dataShare_t* share, string title) {
	graphicsEngine window(length, height, share, title);
}

GUI::GUI() {
    dataShare.lock.unlock();
    thread* graphics = new thread(graphicsThreadFunction, 1920, 1080, &dataShare, "place holder");
}

GUI::~GUI() {

}