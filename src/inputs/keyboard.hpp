#pragma once

#include <SDL.h>
#include <stdio.h>
#include <stack>

namespace ge {
    class Keyboard {
    public:
        enum State { PRESSED, RELEASED, NONE };

        Keyboard();

        void update(SDL_Event &event);

        bool getPress(int key);
        bool getRelease(int key);

        State operator[](int i);

    private:
        State keyboard[239];
        std::stack<int> released;
    };
}