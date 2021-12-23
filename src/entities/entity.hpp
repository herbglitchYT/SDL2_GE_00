#pragma once

#include <SDL.h>
#include <stdint.h>

namespace ge {
    enum class ScaleMode { PERCENT, PX };

    class Entity {
    public:
        Entity(SDL_Texture *spritesheet, SDL_Rect pos);

        virtual ~Entity(){};

        virtual void update(){}

        virtual void render() = 0;
        virtual void render(SDL_FPoint &offset) = 0;

        virtual void setScale(int s, ScaleMode mode) = 0;

        virtual void move(float *x, float *y);
        virtual void move(float  x, float  y);
        virtual void move(SDL_FPoint pos);

        virtual void move(int *x, int *y);
        virtual void move(int  x, int  y);
        virtual void move(SDL_Point pos);

        virtual bool moveTo(SDL_Point coord, float speed);

        virtual void setPos(int *x, int *y);
        virtual void setPos(int  x, int  y);
        virtual void setPos(SDL_Point pos);

        virtual void setPos(float *x, float *y);
        virtual void setPos(float  x, float  y);
        virtual void setPos(SDL_FPoint pos);

    protected:
        SDL_Texture *spritesheet;

        SDL_Rect pos;

        float x, y;
    };
}
