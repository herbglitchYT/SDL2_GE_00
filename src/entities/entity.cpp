#include "entity.hpp"
#include "../ge.hpp"

#include <cmath>

namespace ge {
    Entity::Entity()                               : bounds({ 0, 0, 0, 0 }), pos({ 0.0f, 0.0f })                {}
    Entity::Entity(SDL_FPoint pos)                 : bounds({ 0, 0, 0, 0 }), pos(pos)                           {}
    Entity::Entity(SDL_Point pos)                  : bounds({ 0, 0, 0, 0 }), pos({ (float)pos.x, (float)pos.y }){}
    Entity::Entity(SDL_Rect bounds)                : bounds(bounds),         pos({ 0.0f, 0.0f })                {}
    Entity::Entity(SDL_Rect bounds, SDL_FPoint pos): bounds(bounds),         pos(pos)                           {}
    Entity::Entity(SDL_Rect bounds, SDL_Point pos) : bounds(bounds),         pos({ (float)pos.x, (float)pos.y }){}

    Entity::~Entity(){}

    void Entity::update(){};

    void Entity::move(float *x, float *y){ pos.x += *x * ge::data->dt; pos.y += *y * ge::data->dt; bounds.x = (int)pos.x; bounds.y = (int)pos.y; }
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

    void Entity::setPos(int *x, int *y){ bounds.x = *x; bounds.y = *y; pos.x = (float)*x; pos.y = (float)*y; }
    void Entity::setPos(int  x, int  y){ setPos(&x,     &y    ); }
    void Entity::setPos(SDL_Point pos) { setPos(&pos.x, &pos.y); }

    void Entity::setPos(float *x, float *y){ bounds.x = (int)*x; bounds.y = (int)*y; pos.x = *x; pos.y = *y; }
    void Entity::setPos(float  x, float  y){ setPos(&x,     &y    ); }
    void Entity::setPos(SDL_FPoint pos)    { setPos(&pos.x, &pos.y); }

    SDL_Rect   &Entity::getBounds(){ return bounds; }
    SDL_FPoint &Entity::getPos()   { return pos;    }
}