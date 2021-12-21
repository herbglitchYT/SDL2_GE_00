#pragma once

#include <SDL.h>
#include "sprite.hpp"

namespace ge {
    typedef struct EntityStrs {
        char *bounds;
        char *scale;
        char *group;
    } EntityStrs;

    class Entity : public Sprite {
    public:
        Entity(SDL_Textue *spritesheet, EntityStrs strs = EntityStrs {"bounds", "", ""}, SDL_Point pos = SDL_Point { 0, 0 });
        virtual ~Entity();

    protected:
        int id;
    };
}