#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

namespace ge {
    struct Data;

    typedef struct ColorGrid {
        unsigned int *colors;
        int w, h;
    } ColorGrid;

    class Spritesheet {
    public:
        static SDL_Texture *load(const char *path);
        static ColorGrid loadColorGrid(const char *path);
    };
}