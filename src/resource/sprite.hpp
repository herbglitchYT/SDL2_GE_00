#pragma once

#include <SDL.h>

namespace ge {
    class Sprite {
    public:
        enum class Mode { PERCENT, PX };

        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, SDL_Point pos, int scale = 1);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int scale = 1);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int xPos, int yPos, int scale = 1);
        Sprite(SDL_Texture *spritesheet, int xBound, int yBound, int wBound, int hBound, int xPos = 0, int yPos = 0, int scale = 1);

        void move(float x, float y);
        void move(int x, int y);
        void move(SDL_FPoint pos);
        void move(SDL_Point pos);

        void draw();

        void setPos(float x, float y);
        void setPos(int x, int y);
        void setPos(SDL_FPoint pos);
        void setPos(SDL_Point pos);

        void setBounds(int x, int y, int w, int h);
        void setBounds(SDL_Rect bounds);
        void setBounds(int x, int y);
        void setBounds(SDL_Point pos);

        void setScale(int s, Mode mode = Mode::PERCENT);

        bool collides(int x, int y, int w, int h);
        bool collides(SDL_Rect bounds);
        bool collides(int x, int y);
        bool collides(SDL_Point pos);

        SDL_Rect &getPos();
        SDL_Rect &getBounds();

    private:
        SDL_Rect pos;
        SDL_Rect bounds;
        SDL_Texture *spritesheet;

        int w, h;
        float x, y;
    };
}