#include "ge.hpp"

#include <stdio.h>

ge::Data *ge::data;

int GE::init(int width, int height, const char *title){
    ge::data = new ge::Data();

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: initializing SDL\nSDL Error: ", SDL_GetError());
        return 3;
    }

    ge::data->windowSize = { 0, 0, width, height };
    if(SDL_CreateWindowAndRenderer(ge::data->windowSize.w, ge::data->windowSize.h, 0, &(ge::data->window), &(ge::data->renderer))){
        printf("Error: creating window and renderer\nSDL Error: ", SDL_GetError());
        return 3;
    }

    SDL_SetWindowTitle(ge::data->window, title);
    ge::data->config = ge::Config();

    return 0;
}

int GE::deinit(){
    SDL_DestroyRenderer(ge::data->renderer);
    SDL_DestroyWindow(ge::data->window);

    delete ge::data;
    return 0;
}

int GE::run(){
    float lastTime = 0, currentTime;
    while(true){
        currentTime = SDL_GetTicks();
        ge::data->dt = currentTime - lastTime;
        lastTime = currentTime;

        SDL_PollEvent(&(ge::data->event));
        if(ge::data->event.type == SDL_QUIT){ break; }
        if(ge::data->event.key.keysym.sym == SDLK_ESCAPE && ge::data->event.key.type == SDL_KEYDOWN){ break; }
        ge::data->mouse.update(ge::data->event);
        ge::data->keyboard.update(ge::data->event);

        ge::data->state.update();

        SDL_SetRenderDrawColor(ge::data->renderer, 0x1b, 0x2b, 0x3b, 0x00);
        SDL_RenderClear(ge::data->renderer);
        ge::data->state.render();
        SDL_RenderPresent(ge::data->renderer);
    }

    return 0;
}