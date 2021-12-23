#include "sprite.hpp"
#include "../ge.hpp"

namespace ge {
    Sprite::Sprite(SpriteParams *params): Entity(params->spritesheet, {params->pos.x, params->pos.y, params->bounds.w, params->bounds.h}), bounds(params->bounds), w(params->bounds.w), h(params->bounds.h), angle(0.0){ setScale(params->scale); setCenter(); }
    Sprite::Sprite(SpriteParams  params): Sprite(&params){}
    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int scale):                                                    Sprite(SpriteParams {spritesheet, bounds,                           {0,    0   }, scale}){}
    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, SDL_Point pos, int scale):                                     Sprite(SpriteParams {spritesheet, bounds,                           pos,          scale}){}
    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int xPos, int yPos, int scale):                                Sprite(SpriteParams {spritesheet, bounds,                           {xPos, yPos}, scale}){}
    Sprite::Sprite(SDL_Texture *spritesheet, int xBound, int yBound, int wBound, int hBound, int xPos, int yPos, int scale): Sprite(SpriteParams {spritesheet, {xBound, yBound, wBound, hBound}, {xPos, yPos}, scale}){}

    void Sprite::render(){ SDL_RenderCopy(ge::data->renderer, spritesheet, &bounds, &pos); }

    void Sprite::render(SDL_FPoint &offset){
        SDL_Rect offsetPos = { (int)offset.x + pos.x, (int)offset.y + pos.y, pos.w, pos.h};
        SDL_RenderCopyEx(ge::data->renderer, spritesheet, &bounds, &offsetPos, angle, &center, SDL_FLIP_NONE);
    }

    void Sprite::rotate(double angle){ this->angle = angle; }

    void Sprite::setBounds(int x, int y, int w, int h){ bounds = {x, y, w, h}; }
    void Sprite::setBounds(SDL_Rect bounds){ this->bounds = bounds; }
    void Sprite::setBounds(int x, int y){bounds.x = x; bounds.y = y; }
    void Sprite::setBounds(SDL_Point pos){bounds.x = pos.x; bounds.y = pos.y; }

    void Sprite::setScale(int s, ScaleMode mode){
        if(mode == ScaleMode::PERCENT){ pos.w = w * s; pos.h = h * s; return; }
        if(mode == ScaleMode::PX)     { pos.w = w + s; pos.h = h + s; return; }
    }

    bool Sprite::collides(SDL_Rect *bounds) { return SDL_HasIntersection(&pos, bounds); }
    bool Sprite::collides(SDL_Rect  bounds) { return collides(&bounds); }

    bool Sprite::collides(int  x, int  y){ return collides({x, y, 0, 0}); }
    bool Sprite::collides(SDL_Point pos) { return collides(pos.x, pos.y); }

    void Sprite::setCenter(int x, int y){ center = { x,         y         }; }
    void Sprite::setCenter()            { center = { pos.w / 2, pos.h / 2 }; }

    SDL_Rect &Sprite::getPos()   { return pos;    }
    SDL_Rect &Sprite::getBounds(){ return bounds; }

    SDL_Point &Sprite::getCenter(){ return center; }
}