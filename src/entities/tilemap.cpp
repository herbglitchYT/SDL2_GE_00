#include "tilemap.hpp"
// #include "../ge.hpp"
// #include <stdint.h>

// namespace ge {
//     TileMap::TileMap(SDL_Texture *spritesheet, GE_ColorGrid &colorGrid, GE_Tile tile, SDL_Point *pos, int scale): Entity(pos), colorGrid(colorGrid), tile(tile){
//         for(uint32_t y = 0; y < colorGrid.h; y++){
//             for(uint32_t x = 0; x < colorGrid.w; x++){
                
//             }
//         }
//     }

//     void TileMap::render(){
//         // SDL_Rect offset = { 0 , 0 };
//         // render(offset);
//     }

//     void TileMap::render(SDL_FPoint &offset){
//         // SDL_Rect offsetPos = { (int)offset.x + pos.x, (int)offset.y + pos.y, pos.w, pos.h};
//         // SDL_RenderCopyEx(ge::data->renderer, spritesheet, &bounds, &offsetPos, angle, &center, SDL_FLIP_NONE);
//     }

//     // void TileMap::setScale(int s, ScaleMode mode){

//     // }
// }


/*
                ge::data->config.setGroup("");

                ge::data->config.get(GE_VAR_STR(spritesheet));

                ge::ColorGrid tempMap;
                ge::data->config.get(GE_VAR_STR(tempMap));

                int scale;
                ge::data->config.get(GE_VAR_STR(scale));

                for(int y = 0; y < tile.h; y++){
            for (int x = 0; x < tile.w; x++) {
                unsigned int c = tempMap.colors[x + (y * tempMap.w)];

                if (c == 0xff0000) {
                    add(new Mob(spritesheet, "wallBounds", SDL_Point{x * 32 * scale, y * 32 * scale}));
                    continue;
                }
                if (c == 0x00ff00) {
                    add(new Mob(spritesheet, "pathBounds", SDL_Point{x * 32 * scale, y * 32 * scale}));
                    continue;
                }
                if (c == 0x0000ff) {
                    add(new Mob(spritesheet, "stairsBounds", SDL_Point{x * 32 * scale, y * 32 * scale}));
                }
            }
        }
*/