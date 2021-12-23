#include "entity.hpp"
#include "../ge.hpp"

#include <cmath>

namespace ge {
    Entity::Entity(SDL_Texture *spritesheet, SDL_Rect pos): spritesheet(spritesheet), pos(pos), x((float)pos.x), y((float)pos.y){}

    void Entity::move(float *x, float *y){ this->x += *x * ge::data->dt; this->y += *y * ge::data->dt; pos.x = (int)this->x; pos.y = (int)this->y; }
    void Entity::move(float  x, float  y){ move(&x,     &y    ); }
    void Entity::move(SDL_FPoint pos)    { move(&pos.x, &pos.y); }

    void Entity::move(int *x, int *y){ move((float *)x, (float *)y); }
    void Entity::move(int  x, int  y){ move(&x, &y); }
    void Entity::move(SDL_Point pos) { move(&pos.x, &pos.y); }

    bool Entity::moveTo(SDL_Point coord, float speed){
        float angle = atan2(coord.y - pos.y, coord.x - pos.x);
        move(speed * cosf(angle), speed * sinf(angle));
        return pos.x == coord.x && pos.y == coord.y;
    }

    void Entity::setPos(int *x, int *y){ pos.x = *x; pos.y = *y; this->x = (float)*x; this->y = (float)*y; }
    void Entity::setPos(int  x, int  y){ setPos(&x,     &y    ); }
    void Entity::setPos(SDL_Point pos) { setPos(&pos.x, &pos.y); }

    void Entity::setPos(float *x, float *y){ pos.x = (int)*x; pos.y = (int)*y; this->x = *x; this->y = *y; }
    void Entity::setPos(float  x, float  y){ setPos(&x,     &y    ); }
    void Entity::setPos(SDL_FPoint pos)    { setPos(&pos.x, &pos.y); }
}