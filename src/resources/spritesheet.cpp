#include "spritesheet.hpp"
#include "../ge.hpp"
#include <stdint.h>

namespace ge {
    SDL_Texture *Spritesheet::load(const char *path){
        IMG_Init(IMG_INIT_PNG);
        SDL_Surface *surface = IMG_Load(path);
        if(!surface){ printf("Error: reading png '%s'\nSDL_Image Error: %s", path, IMG_GetError()); }

        SDL_Texture *spritesheet = SDL_CreateTextureFromSurface(ge::data->renderer, surface);

        SDL_FreeSurface(surface);
        IMG_Quit();

        return spritesheet;
    }

    ColorGrid *Spritesheet::loadColorGrid(const char *path){
        IMG_Init(IMG_INIT_PNG);
        SDL_Surface *surface = IMG_Load(path);
        if(!surface){ printf("Error: reading png '%s'\nSDL_Image Error: %s", path, IMG_GetError()); }

        ColorGrid *grid = new ColorGrid { new uint32_t[surface->w * surface->h], (uint32_t)surface->w, (uint32_t)surface->h };

        for(int i = 0; i < surface->w * surface->h; i++){
            SDL_Color color = surface->format->palette->colors[*((uint8_t *)surface->pixels + i)];
            grid->colors[i] = ((color.r & 0xff) << 16) + ((color.g & 0xff) << 8) + (color.b & 0xff);
        }

        SDL_FreeSurface(surface);
        IMG_Quit();

        return grid;
    }
}