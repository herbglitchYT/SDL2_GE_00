#include "sprite.hpp"
#include "../ge.hpp"

namespace ge {
    Sprite::Sprite(SpriteParams *params): spritesheet(params->spritesheet), bounds(params->bounds), pos({params->pos.x, params->pos.y, params->bounds.w, params->bounds.h}), w(params->bounds.w), h(params->bounds.h), x((float)params->pos.x), y((float)params->pos.y), angle(0.0){ setScale(params->scale); setCenter(); }
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

    void Sprite::move(int *x, int *y){ pos.x += *x; pos.y += *y; this->x = (float)pos.x; this->y = (float)pos.y; }
    void Sprite::move(int  x, int  y){ move(&x, &y); }
    void Sprite::move(SDL_Point pos) { move(&pos.x, &pos.y); }

    void Sprite::move(float *x, float *y){ this->x += *x; this->y += *y; pos.x = (int)this->x; pos.y = (int)this->y; }
    void Sprite::move(float  x, float  y){ move(&x,     &y    ); }
    void Sprite::move(SDL_FPoint pos)    { move(&pos.x, &pos.y); }

    void Sprite::moveTo(SDL_FPoint coord, float speed){
        if(pos.x == coord.x && pos.y == coord.y){ return; }
        if(coord.x - pos.x){
            pos.x += (coord.x - pos.x > 0)?
                ((coord.x - pos.x <         speed * ge::data->dt)? coord.x - pos.x :         speed * ge::data->dt):
                ((coord.x - pos.x > -1.0f * speed * ge::data->dt)? coord.x - pos.x : -1.0f * speed * ge::data->dt);
        }
        if(coord.y - pos.y){
            pos.y += (coord.y - pos.y > 0)?
                ((coord.y - pos.y <         speed * ge::data->dt)? coord.y - pos.y :         speed * ge::data->dt):
                ((coord.y - pos.y > -1.0f * speed * ge::data->dt)? coord.y - pos.y : -1.0f * speed * ge::data->dt);
        }
    }

    void Sprite::setPos(int *x, int *y){ pos.x = *x; pos.y = *y; this->x = (float)*x; this->y = (float)*y; }
    void Sprite::setPos(int  x, int  y){ setPos(&x,     &y    ); }
    void Sprite::setPos(SDL_Point pos) { setPos(&pos.x, &pos.y); }

    void Sprite::setPos(float *x, float *y){ pos.x = (int)*x; pos.y = (int)*y; this->x = *x; this->y = *y; }
    void Sprite::setPos(float  x, float  y){ setPos(&x,     &y    ); }
    void Sprite::setPos(SDL_FPoint pos)    { setPos(&pos.x, &pos.y); }

    void Sprite::setBounds(int x, int y, int w, int h){ bounds = {x, y, w, h}; }
    void Sprite::setBounds(SDL_Rect bounds){ this->bounds = bounds; }
    void Sprite::setBounds(int x, int y){bounds.x = x; bounds.y = y; }
    void Sprite::setBounds(SDL_Point pos){bounds.x = pos.x; bounds.y = pos.y; }

    void Sprite::setScale(int s, Mode mode){
        if(mode == Mode::PERCENT){ pos.w = w * s; pos.h = h * s; return; }
        if(mode == Mode::PX)     { pos.w = w + s; pos.h = h + s; return; }
    }

    bool Sprite::collides(int *x, int *y, int *w, int *h){ return *x + *w >= pos.x && *x <= pos.x + pos.w && *y + *h <= pos.y && *y >= pos.y + pos.h; }
    bool Sprite::collides(int  x, int  y, int  w, int  h){ return collides(&x,        &y,        &w,        &h       ); }
    bool Sprite::collides(SDL_Rect bounds)               { return collides(&bounds.x, &bounds.y, &bounds.w, &bounds.h); }

    bool Sprite::collides(int *x, int *y){ return *x >= pos.x && *x <= pos.x + pos.w && *y >= pos.y && *y <= pos.y + pos.w; }
    bool Sprite::collides(int  x, int  y){ return collides(&x,     &y    ); }
    bool Sprite::collides(SDL_Point pos) { return collides(&pos.x, &pos.y); }

    void Sprite::setCenter(int x, int y){ center = { x,         y         }; }
    void Sprite::setCenter()            { center = { pos.w / 2, pos.h / 2 }; }

    SDL_Rect &Sprite::getPos()   { return pos;    }
    SDL_Rect &Sprite::getBounds(){ return bounds; }

    SDL_Point &Sprite::getCenter(){ return center; }
}