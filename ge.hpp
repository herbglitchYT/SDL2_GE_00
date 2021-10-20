#ifndef GE_HPP
#define GE_HPP

#include <SDL.h>
#include <stdio.h>
#include "config.hpp"
#include "handler.hpp"
#include "object.hpp"
#include "input/mouse.hpp"
#include "input/keyboard.hpp"
#include "resource/spritesheet.hpp"
#include "resource/sprite.hpp"

#define ge_run(state, width, height, title) GE::Run<state>(width, height, title);
#define ge_main(state, width, height, title) int main(int argc, char *argv[]){\
    return ge_run(state, width, height, title); }

namespace ge {
    struct Data {
        Handler<Object> state;
        Config config;

        Mouse mouse;
        Keyboard keyboard;

        SDL_Window *window;
        SDL_Rect windowSize;

        SDL_Renderer *renderer;

        SDL_Event event;

        float scale = 8.0f;
        float dt;
    };
}

class GE {
public:
    template <class initState>
    static int Run(int width, int height, const char *title){
        ge::Data *data = new ge::Data();

        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            printf("Error: initializing SDL\nSDL Error: ", SDL_GetError());
            return 3;
        }

        data->windowSize = { 0, 0, width, height };
        if(SDL_CreateWindowAndRenderer(data->windowSize.w, data->windowSize.h, 0, &(data->window), &(data->renderer))){
            printf("Error: creating window and renderer\nSDL Error: ", SDL_GetError());
            return 3;
        }

        SDL_SetWindowTitle(data->window, title);

        data->config = ge::Config(data->renderer);
        data->state.add(new initState(data));

        float lastTime = 0, currentTime;
        while(true){
            currentTime = SDL_GetTicks();
            data->dt = currentTime - lastTime;
            lastTime = currentTime;

            SDL_PollEvent(&(data->event));
            if(data->event.type == SDL_QUIT){ break; }
            if(data->event.key.keysym.sym == SDLK_ESCAPE && data->event.key.type == SDL_KEYDOWN){ break; }
            data->mouse.update(data->event);
            // data->keyboard.update(data->event);

            data->state.update();

            SDL_SetRenderDrawColor(data->renderer, 0x33, 0x48, 0x57, 0x00);
            SDL_RenderClear(data->renderer);
            data->state.render();
            SDL_RenderPresent(data->renderer);
        }

        SDL_DestroyRenderer(data->renderer);
        SDL_DestroyWindow(data->window);

        delete data;

        return 0;
    }
};

#endif // !GE_HPP
