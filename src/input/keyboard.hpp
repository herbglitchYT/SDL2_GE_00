#pragma once

#include <SDL.h>
#include <stdio.h>

namespace ge {
    class Keyboard {
    public:
        enum State { PRESSED, RELEASED };

        Keyboard(){
            for(unsigned int i = 0; i < 239; i++){ keyboard[i] = RELEASED; }
        }

        void update(SDL_Event &event){
            if(event.key.keysym.sym >= 239){ return; }

            if(event.key.state == SDL_PRESSED || event.motion.state == SDL_PRESSED){
                keyboard[event.key.keysym.sym] = PRESSED;
                return;
            }

            if(event.key.state == PRESSED && event.key.state == SDL_RELEASED){
                keyboard[event.key.keysym.sym] = RELEASED;
            }
        }

        State operator[](int i){ return keyboard[i]; }

    private:
        State keyboard[239];
    };
}