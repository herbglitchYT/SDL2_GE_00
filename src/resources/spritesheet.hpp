#pragma once

#include "../types/types.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

namespace ge {
    class Spritesheet {
    public:
        static SDL_Texture *load(const char *path);
        static GE_ColorGrid *loadColorGrid(const char *path);
    };
}