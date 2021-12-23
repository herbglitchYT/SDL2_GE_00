#pragma once

#include <SDL.h>
#include "entity.hpp"

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

    class Sprite : public Entity {
    public:
        Sprite(SpriteParams *params);
        Sprite(SpriteParams  params);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int scale = 1);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, SDL_Point pos, int scale = 1);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int xPos, int yPos, int scale = 1);
        Sprite(SDL_Texture *spritesheet, int xBound, int yBound, int wBound, int hBound, int xPos = 0, int yPos = 0, int scale = 1);

        void render() override;
        void render(SDL_FPoint &offset) override;

        void rotate(double angle);

        void setBounds(int x, int y, int w, int h);
        void setBounds(SDL_Rect bounds);
        void setBounds(int x, int y);
        void setBounds(SDL_Point pos);

        void setScale(int s, ScaleMode mode = ScaleMode::PERCENT) override;

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
        SDL_Rect bounds;

        SDL_Point center;
        double angle;

        int w, h;
    };
}