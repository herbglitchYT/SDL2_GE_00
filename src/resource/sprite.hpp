#pragma once

#include <SDL.h>
#include "object.hpp"

namespace ge {
    typedef struct SpriteParams {
        SDL_Texture *spritesheet;
        SDL_Rect bounds;
        SDL_Point pos;
        int scale;
    } SpriteParams;

    typedef struct SpriteStrs {
        const char *bounds = nullptr;
        const char *scale  = nullptr;
        const char *group  = nullptr;
    } SpriteStrs;

    class Sprite {
    public:
        enum class Mode { PERCENT, PX };

        Sprite(){}

        Sprite(SpriteParams *params);
        Sprite(SpriteParams  params);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int scale = 1);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, SDL_Point pos, int scale = 1);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int xPos, int yPos, int scale = 1);
        Sprite(SDL_Texture *spritesheet, int xBound, int yBound, int wBound, int hBound, int xPos = 0, int yPos = 0, int scale = 1);

        virtual void update(){}

        void render();
        void render(SDL_FPoint &offset);

        void rotate(double angle);

        void move(int *x, int *y);
        void move(int  x, int  y);
        void move(SDL_Point pos);

        void move(float *x, float *y);
        void move(float  x, float  y);
        void move(SDL_FPoint pos);

        void moveTo(SDL_Point coord, float speed);

        void setPos(int *x, int *y);
        void setPos(int  x, int  y);
        void setPos(SDL_Point pos);

        void setPos(float *x, float *y);
        void setPos(float  x, float  y);
        void setPos(SDL_FPoint pos);

        void setBounds(int x, int y, int w, int h);
        void setBounds(SDL_Rect bounds);
        void setBounds(int x, int y);
        void setBounds(SDL_Point pos);

        void setScale(int s, Mode mode = Mode::PERCENT);

        bool collides(int *x, int *y, int *w, int *h);
        bool collides(int  x, int  y, int  w, int  h);
        bool collides(SDL_Rect bounds);

        bool collides(int *x, int *y);
        bool collides(int  x, int  y);
        bool collides(SDL_Point pos);

        void setCenter();
        void setCenter(int x, int y);

        SDL_Rect &getPos();
        SDL_Rect &getBounds();

        SDL_Point &getCenter();

    protected:
        SDL_Texture *spritesheet;

        SDL_Rect pos;
        SDL_Rect bounds;

        SDL_Point center;

        int w, h;
        float x, y;
        double angle;
    };
}