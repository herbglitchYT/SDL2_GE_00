#include "spritesheet.hpp"

//avoid circular reference
#include "../ge.hpp"

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
}