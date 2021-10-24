#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

namespace ge {
    struct Data;

    class Spritesheet {
    public:
        static SDL_Texture *load(const char *path);

    };
}