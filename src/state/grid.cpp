#include "grid.hpp"
#include "../ge.hpp"

namespace ge {
    Grid::Grid(SDL_FPoint offset, SDL_Point tileSize): Surface(offset), tileSize(tileSize){
        surfaceSize.x = (ge::data->windowSize.w / tileSize.x) + (ge::data->windowSize.w % tileSize.x)? 1 : 0;
        surfaceSize.y = (ge::data->windowSize.h / tileSize.y) + (ge::data->windowSize.h % tileSize.y)? 1 : 0;
    
        positions = new Sprite[surfaceSize.x * surfaceSize.y];
    }

    Grid::Grid():                   Grid({0.0f, 0.0f}, {1, 1}  ){}
    Grid::Grid(SDL_FPoint offset):  Grid(offset,       {1, 1}  ){}
    Grid::Grid(SDL_Point tileSize): Grid({0.0f, 0.0f}, tileSize){}

    Grid::Grid(int tileSize):                    Grid({0.0f, 0.0f}, {tileSize, tileSize}){}
    Grid::Grid(SDL_FPoint offset, int tileSize): Grid(offset,       {tileSize, tileSize}){}

    Grid::~Grid(){ delete [] positions; };

    SDL_Point Grid::gridPoint(SDL_Point *point){ return SDL_Point{ point->x/ tileSize.x, point->y / tileSize.y }; }
    SDL_Point Grid::gridPoint(SDL_Point  point){ return gridPoint(point); }
}
