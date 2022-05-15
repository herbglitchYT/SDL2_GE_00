#pragma once

#include <SDL.h>
#include <stdio.h>

namespace ge {
    class Keyboard {
    public:
        enum State { NONE, PRESSED, RELEASED };

        void update(SDL_Event &event){
            if(released){
                *released = State::NONE;
                released = nullptr;
            }

            if(event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)   { return; }
            if(event.key.keysym.sym >= 239 || event.key.keysym.sym < 0){ return; }

            if(event.type == SDL_KEYDOWN){
                keyboard[event.key.keysym.sym] = PRESSED;
                return;
            }

            keyboard[event.key.keysym.sym] = RELEASED;
            released = (keyboard + event.key.keysym.sym);
        }

        bool getPress  (int key){ return keyboard[key] == State::PRESSED;  }
        bool getRelease(int key){ return keyboard[key] == State::RELEASED; }

        State operator[](int key){ return keyboard[key]; }

    private:
        State keyboard[239] = { NONE };
        State *released = nullptr;
    };
}