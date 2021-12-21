#include "sprite.hpp"
#include "../ge.hpp"

namespace ge {
    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, SDL_Point pos, int scale): spritesheet(spritesheet), bounds(bounds), pos({pos.x, pos.y, bounds.w, bounds.h}), w(bounds.w), h(bounds.h), x((float)pos.x), y((float)pos.y), angle(0.0){
        setScale(scale);
        setCenter();
    }

    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int scale): Sprite(spritesheet, bounds, {0, 0}, scale){}
    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int xPos, int yPos, int scale): Sprite(spritesheet, bounds, {xPos, yPos}, scale){}
    Sprite::Sprite(SDL_Texture *spritesheet, int xBound, int yBound, int wBound, int hBound, int xPos, int yPos, int scale): Sprite(spritesheet, {xBound, yBound, wBound, hBound}, {xPos, yPos}, scale){}

    void Sprite::draw(SDL_FPoint &offset){
        SDL_Rect offsetPos = { (int)offset.x + pos.x, (int)offset.y + pos.y, pos.w, pos.h};
        if(!collides(ge::data->windowSize)){ return; }
        SDL_RenderCopyEx(ge::data->renderer, spritesheet, &bounds, &pos, angle, &center, SDL_FLIP_NONE);
    }

    void Sprite::move(float x, float y){ this->x += x; this->y += y; pos.x = (int)this->x; pos.y = (int)this->y; }
    void Sprite::move(int x, int y){ pos.x += x; pos.y += y; this->x = (float)pos.x; this->y = (float)pos.y; }
    void Sprite::move(SDL_FPoint pos){ x += pos.x; y = pos.y; this->pos.x = (int)x; this->pos.y = (int)y; }
    void Sprite::move(SDL_Point pos){ this->pos.x += pos.x; this->pos.y += pos.y; x = (float)this->pos.x; y = (float)this->pos.y; }

    void Sprite::rotate(double angle){ this->angle = angle; }

    void Sprite::setPos(float x, float y){ pos.x = (int)x; pos.y = (int)y; this->x = x; this->y = y; }
    void Sprite::setPos(int x, int y){ pos.x = x; pos.y = y; this->x = (float)x; this->y = (float)y; }
    void Sprite::setPos(SDL_FPoint pos){ this->pos.x = (int)pos.x; this->pos.y = (int)pos.y; x = pos.x; y = pos.y; }
    void Sprite::setPos(SDL_Point pos){ this->pos.x = pos.x; this->pos.y = pos.y; x = (float)pos.x; y = (float)pos.y; }

    void Sprite::setBounds(int x, int y, int w, int h){ bounds = {x, y, w, h}; }
    void Sprite::setBounds(SDL_Rect bounds){ this->bounds = bounds; }
    void Sprite::setBounds(int x, int y){bounds.x = x; bounds.y = y; }
    void Sprite::setBounds(SDL_Point pos){bounds.x = pos.x; bounds.y = pos.y; }

    void Sprite::setScale(int s, Mode mode){
        if(mode == Mode::PERCENT){ pos.w = w * s; pos.h = h * s; return; }
        if(mode == Mode::PX){ pos.w = w + s; pos.h = h + s; return; }
    }

    bool Sprite::collides(int x, int y, int w, int h){ return x + w > pos.x && x < pos.x + pos.w && y + h > pos.y && y < pos.y + pos.h; }
    bool Sprite::collides(SDL_Rect bounds){ return collides(bounds.x, bounds.y, bounds.w, bounds.h); }
    bool Sprite::collides(int x, int y){ return x > pos.x && x < pos.x + pos.w && y > pos.y && y < pos.y + pos.w; }
    bool Sprite::collides(SDL_Point pos){ return collides(pos.x, pos.y); }

    void Sprite::setCenter(){ center = SDL_Point { pos.w / 2, pos.h / 2 }; }

    SDL_Rect &Sprite::getPos(){ return pos; }
    SDL_Rect &Sprite::getBounds(){ return bounds; }

    SDL_Point &Sprite::getCenter(){ return center; }
}