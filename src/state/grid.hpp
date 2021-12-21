#pragma once

#include <SDL.h>
#include "handler.hpp"

namespace ge {
    typedef struct Tile {
        int x, y;
        unsigned int w, h;
    } Tile;

    class State : public Handler<Tile> {
    public:
        State(){ offset = {0.0f, 0.0f}; }
        virtual ~State(){};

        virtual void update(){};

        virtual void render(){
            // for(Tile *tile : hTypes){ object->draw(offset); }
        };

    protected:
        unsigned int w, h;
    };
}
