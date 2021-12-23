#pragma once

#include "surface.hpp"
#include "../entity/sprite.hpp"

namespace ge {
    class Grid : public Surface {
    public:
        Grid(SDL_FPoint offset, SDL_Point tileSize);

        Grid();
        Grid(SDL_FPoint offset);
        Grid(SDL_Point tileSize);

        Grid(int tileSize);
        Grid(SDL_FPoint offset, int tileSize);

        virtual ~Grid();

        SDL_Point gridPoint(SDL_Point *point);
        SDL_Point gridPoint(SDL_Point  point);

    protected:
        SDL_Point tileSize, surfaceSize;

        Sprite *positions;
    };
}
