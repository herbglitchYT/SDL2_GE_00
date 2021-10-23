#pragma once

#include <SDL.h>

namespace ge {
    class Sprite {
    public:
        Sprite(SDL_Texture *spritesheet, int xBound, int yBound, int wBound, int hBound, int xPos, int yPos);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, int xPos, int yPos);
        Sprite(SDL_Texture *spritesheet, SDL_Rect bounds, SDL_Point pos);

        void move(float x, float y);
        void move(int x, int y);
        void move(SDL_FPoint pos);
        void move(SDL_Point pos);

        void draw(SDL_Renderer *renderer);

        void setPos(float x, float y);
        void setPos(int x, int y);
        void setPos(SDL_FPoint pos);
        void setPos(SDL_Point pos);

        void setBounds(int x, int y, int w, int h);
        void setBounds(SDL_Rect bounds);
        void setBounds(int x, int y);
        void setBounds(SDL_Point pos);

        void setScale(int s);

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