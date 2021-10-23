#include "sprite.hpp"

namespace ge {
    Sprite::Sprite(SDL_Texture *spritesheet, int xBound, int yBound, int wBound, int hBound, int xPos, int yPos): spritesheet(spritesheet), bounds(SDL_Rect {xBound, yBound, wBound, hBound}), pos(SDL_Rect {xPos, yPos, wBound, hBound}), w(bounds.w), h(bounds.h), x((float)xPos), y((float)yPos){}
    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int xPos, int yPos): spritesheet(spritesheet), bounds(bounds), pos(SDL_Rect {xPos, yPos, bounds.w, bounds.h}), w(bounds.w), h(bounds.h), x((float)xPos), y((float)yPos){}
    Sprite::Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, SDL_Point pos): spritesheet(spritesheet), bounds(bounds), pos(SDL_Rect {pos.x, pos.y, bounds.w, bounds.h}), w(bounds.w), h(bounds.h), x((float)pos.x), y((float)pos.y){}

    void Sprite::move(float x, float y){ this->x += x; this->y += y; pos.x = (int)this->x; pos.y = (int)this->y; }
    void Sprite::move(int x, int y){ pos.x += x; pos.y += y; this->x = (float)pos.x; this->y = (float)pos.y; }
    void Sprite::move(SDL_FPoint pos){ x += pos.x; y = pos.y; this->pos.x = (int)x; this->pos.y = (int)y; }
    void Sprite::move(SDL_Point pos){ this->pos.x += pos.x; this->pos.y += pos.y; x = (float)this->pos.x; y = (float)this->pos.y; }

    void Sprite::draw(SDL_Renderer *renderer){ SDL_RenderCopy(renderer, spritesheet, &bounds, &pos); }

    void Sprite::setPos(float x, float y){ pos.x = (int)x; pos.y = (int)y; this->x = x; this->y = y; }
    void Sprite::setPos(int x, int y){ pos.x = x; pos.y = y; this->x = (float)x; this->y = (float)y; }
    void Sprite::setPos(SDL_FPoint pos){ this->pos.x = (int)pos.x; this->pos.y = (int)pos.y; x = pos.x; y = pos.y; }
    void Sprite::setPos(SDL_Point pos){ this->pos.x = pos.x; this->pos.y = pos.y; x = (float)pos.x; y = (float)pos.y; }

    void Sprite::setBounds(int x, int y, int w, int h){ bounds = {x, y, w, h}; }
    void Sprite::setBounds(SDL_Rect bounds){ this->bounds = bounds; }
    void Sprite::setBounds(int x, int y){bounds.x = x; bounds.y = y; }
    void Sprite::setBounds(SDL_Point pos){bounds.x = pos.x; bounds.y = pos.y; }

    void Sprite::setScale(int s){ pos.w = w * s; pos.h = h * s; }

    SDL_Rect &Sprite::getPos(){ return pos; }
    SDL_Rect &Sprite::getBounds(){ return bounds; }
}