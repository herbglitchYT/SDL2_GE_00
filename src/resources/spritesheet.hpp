#pragma once

#include "../types/colorgrid.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

namespace ge {
    class Spritesheet {
    public:
        static SDL_Texture *load(const char *path);
        static ColorGrid *loadColorGrid(const char *path);
    };
}