#pragma once

#include "entity.hpp"
#include "../types/tile.hpp"
#include "../types/colorgrid.hpp"
#include <SDL.h>

namespace ge {
    class TileMap : public Entity {
    public:
        TileMap(SDL_Texture *spritesheet, ColorGrid &colorGrid, Tile tile, SDL_Point pos, int scale);
        virtual ~TileMap(){}

        void render();
        void render(SDL_FPoint &offset);

        void setScale(int s, ScaleMode mode = ScaleMode::PERCENT);

    protected:
        ColorGrid colorGrid;

        Tile tile;
    };
}