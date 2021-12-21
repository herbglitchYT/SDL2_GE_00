#include "entity.hpp"
#include "../ge.hpp"

#include <string.h>

namespace ge {
    Entity::Entity(SDL_Texture *spritesheet, EntityStrs strs, SDL_Point pos): Sprite(spritesheet, { 0, 0, 0, 0 }, pos){
        data->config.setGroup(strs.group? strs.group : "");

        data->config.get(strs.bounds? strs.bounds : "bounds", bounds);
        this->pos = { pos.x, pos.y, bounds.w, bounds.h };

        w = bounds.w;
        h = bounds.h;

        if(strs.scale){
            int scale;
            data->config.get(strs.scale, scale);
            setScale(scale);
        }
    }

    Entity::Entity(SDL_Texture *spritesheet, EntityStrs strs): Entity(spritesheet, strs, SDL_Point { 0, 0 }){}

    Entity::~Entity(){}
}