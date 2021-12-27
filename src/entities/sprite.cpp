#include "sprite.hpp"
#include "../ge.hpp"

namespace ge {
    Sprite::Sprite(GE_Sprite *sprite)                                : Entity(   ), sprite(sprite), angle(0.0f) {       scale(1);     setCenter(); }
    Sprite::Sprite(GE_Sprite *sprite, SDL_Point pos)                 : Entity(pos), sprite(sprite), angle(0.0f) {       scale(1);     setCenter(); }
    Sprite::Sprite(GE_Sprite *sprite, SDL_FPoint pos)                : Entity(pos), sprite(sprite), angle(0.0f) {       scale(1);     setCenter(); }
    Sprite::Sprite(GE_Sprite *sprite, GE_Scale scale)                : Entity(   ), sprite(sprite), angle(0.0f) { this->scale(scale); setCenter(); }
    Sprite::Sprite(GE_Sprite *sprite, GE_Scale scale, SDL_Point pos) : Entity(pos), sprite(sprite), angle(0.0f) { this->scale(scale); setCenter(); }
    Sprite::Sprite(GE_Sprite *sprite, GE_Scale scale, SDL_FPoint pos): Entity(pos), sprite(sprite), angle(0.0f) { this->scale(scale); setCenter(); }

    void Sprite::render(){ SDL_RenderCopy(ge::data->renderer, sprite->sheet, sprite->bounds, &bounds); }

    void Sprite::render(SDL_FPoint &offset){
        SDL_Rect offsetBounds = {(int)offset.x + bounds.x, (int)offset.y + bounds.y, bounds.w, bounds.h};
        SDL_RenderCopyEx(ge::data->renderer, sprite->sheet, sprite->bounds, &offsetBounds, angle, &center, SDL_FLIP_NONE);
    }

    void Sprite::rotate(double angle){ this->angle = angle; }

    void Sprite::scale(GE_Scale scale, GE_ScaleMode mode){
        if(mode == GE_PERCENT){ bounds.w = sprite->bounds->w * scale; bounds.h = sprite->bounds->h * scale; return; }
        if(mode == GE_PX)     { bounds.w = sprite->bounds->w + scale; bounds.h = sprite->bounds->h + scale; return; }
    }

    bool Sprite::collides(SDL_Rect *bounds){ return SDL_HasIntersection(&this->bounds, bounds); }
    bool Sprite::collides(SDL_Rect  bounds){ return collides(&bounds); }

    bool Sprite::collides(int x, int y) { return collides({x, y, 0, 0}); }
    bool Sprite::collides(SDL_Point pos){ return collides(pos.x, pos.y); }

    void Sprite::setCenter(){ center = { bounds.h / 2, bounds.h / 2 }; }
    void Sprite::setCenter(int x, int y) { center = { x, y }; }
    void Sprite::setCenter(SDL_Point pos){ center = pos; }

    SDL_Point &Sprite::getCenter(){ return center; }
}