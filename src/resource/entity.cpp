#include "entity.hpp"
#include "../ge.hpp"

#include <string.h>

namespace ge {
    Entity::Entity(SDL_Texture *spritesheet, EntityStrs strs, SDL_Point pos){
        data->config.setGroup(group);

        SDL_Rect bounds;
        int scale;

        data->config.get(boundsStr, strs.bounds);
        if(strcmp("", sts.scale)){
            Sprite::Sprite(spritesheet, bounds, SDL_Point pos);
            return;
        }

        data->config.get(scaleStr, strs.scale);
        Sprite::Sprite(spritesheet, bounds, SDL_Point pos, scale);
    }

    Entity::~Entity(){}
}