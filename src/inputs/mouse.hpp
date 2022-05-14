#pragma once

#include <SDL.h>

namespace ge {
    class Mouse {
    public:
        enum State { NONE, PRESSED, RELEASED };

        void update(SDL_Event &event){
            if(released){
                *released = State::NONE;
                released = nullptr;
            }

            button = SDL_GetMouseState(&x, &y);

            if(event.type != SDL_MOUSEBUTTONDOWN && event.type != SDL_MOUSEBUTTONUP){ return; }
            if(event.button.button < 1 || event.button.button > 6)  { return; }

            if(event.type == SDL_MOUSEBUTTONDOWN){
                mouse[event.button.button - 1] = State::PRESSED;
                return;
            }

            mouse[event.button.button - 1] = State::RELEASED;
            released = (mouse + event.button.button - 1);
        }

        bool getPress  (int key){ return mouse[key - 1] == State::PRESSED;  }
        bool getRelease(int key){ return mouse[key - 1] == State::RELEASED; }

        State &operator[](int i){ return mouse[i - 1]; }

        int x, y;
        Uint32 button; //TODO: use button

    private:
        State mouse[5] = { NONE };
        State *released = nullptr;
    };
}
