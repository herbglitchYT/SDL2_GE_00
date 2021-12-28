#pragma once

#include "entity.hpp"
#include "../types/types.h"
#include <SDL.h>
#include <stdint.h>

namespace ge {
    class Sprite : public Entity {
    public:
        Sprite(GE_Sprite *sprite);
        Sprite(GE_Sprite *sprite, SDL_Point pos);
        Sprite(GE_Sprite *sprite, SDL_FPoint pos);
        Sprite(GE_Sprite *sprite, GE_Scale scale);
        Sprite(GE_Sprite *sprite, GE_Scale scale, SDL_Point pos);
        Sprite(GE_Sprite *sprite, GE_Scale scale, SDL_FPoint pos);

        void render() override;
        void render(SDL_FPoint &offset) override;

        void rotate(double angle);

        void scale(GE_Scale scale, GE_ScaleMode mode = GE_PERCENT);

        bool collides(SDL_Rect *bounds);
        bool collides(SDL_Rect  bounds);

        bool collides(int  x, int  y);
        bool collides(SDL_Point pos);

        void setCenter();
        void setCenter(int x, int y);
        void setCenter(SDL_Point pos);

        void setSprite(GE_Sprite *sprite);

        SDL_Point &getCenter();

    protected:
        GE_Sprite *sprite;

        SDL_Point center;

        double angle;
    };
}