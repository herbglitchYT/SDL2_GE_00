#pragma once

#include <SDL.h>
#include <stdint.h>

namespace ge {
    class Entity {
    public:
        Entity();
        Entity(SDL_FPoint pos);
        Entity(SDL_Point pos);
        Entity(SDL_Rect bounds);
        Entity(SDL_Rect bounds, SDL_FPoint pos);
        Entity(SDL_Rect bounds, SDL_Point pos);

        virtual ~Entity();

        virtual void update();

        virtual void render() = 0;
        virtual void render(SDL_FPoint &offset) = 0;

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

        SDL_Rect   &getBounds();
        SDL_FPoint &getPos();

    protected:
        SDL_Rect bounds;
        SDL_FPoint pos;
    };
}
