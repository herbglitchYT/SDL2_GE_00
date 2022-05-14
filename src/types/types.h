#ifndef GE_TYPES_H_
#define GE_TYPES_H_

#include <SDL.h>
#include <stdint.h>
//Every type in this file can be used in config

typedef uint32_t GE_Scale;
typedef uint32_t GE_Color; //r, g, b, a

typedef struct SDL_Texture GE_Sheet;
typedef struct SDL_Rect    GE_Bounds;

typedef enum { GE_PERCENT, GE_PX } GE_ScaleMode;

typedef struct GE_Tile {
    uint32_t w, h;
} GE_Tile;

typedef struct GE_Sprite {
    GE_Sheet  *sheet;
    GE_Bounds *bounds;
} GE_Sprite;

typedef struct GE_ColorGrid {
    GE_Color *colors;
    uint32_t w, h;
} GE_ColorGrid;

#endif