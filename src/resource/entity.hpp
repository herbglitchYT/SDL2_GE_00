#pragma once

#include <SDL.h>
#include "sprite.hpp"

namespace ge {
    typedef struct EntityStrs {
        const char *bounds = nullptr;
        const char *scale  = nullptr;
        const char *group  = nullptr;
    } EntityStrs;

    class Entity : public Sprite {
    public:
        Entity(SDL_Texture *spritesheet, EntityStrs strs);
        Entity(SDL_Texture *spritesheet, EntityStrs strs, SDL_Point pos);
        virtual ~Entity();

    protected:
        int id;
    };
}