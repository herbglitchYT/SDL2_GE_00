#pragma once

#include <SDL.h>

namespace ge {
    class Mouse {
    public:
        enum State { NONE, PRESSED, RELEASED };

        void update(SDL_Event &event){
            button = SDL_GetMouseState(&x, &y);

            for(int i = 0; i < 5; i++){
                if((event.button.state == SDL_PRESSED || event.motion.state == SDL_PRESSED) && event.button.button == (i + 1)){
                    mouse[i] = PRESSED;
                    continue;
                }

                if(mouse[i] == PRESSED && event.button.state == SDL_RELEASED && event.button.button == (i + 1)){
                    mouse[i] = RELEASED;
                    continue;
                }

                if(mouse[i] == RELEASED){
                    mouse[i] = NONE;
                }
            }
        }

        State &operator[](int i){ return mouse[i - 1]; }

        int x, y;
        Uint32 button; //TODO: use button

    private:
        State mouse[5];
    };
}
