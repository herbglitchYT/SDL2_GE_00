#pragma once

#include <SDL.h>
#include <stdio.h>

namespace ge {
    class Keyboard {
    public:
        enum State { PRESSED, RELEASED };

        Keyboard();

        void update(SDL_Event &event);

        State operator[](int i){ return keyboard[i]; }

    private:
        State keyboard[239];
    };
}