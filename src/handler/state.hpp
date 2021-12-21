#pragma once

#include <SDL.h>
#include "../resource/object.hpp"
#include "handler.hpp"

typedef ge::Handler<ge::Object> StateHandler; 

namespace ge {
    class State : public Handler<Object> {
    public:
        State(){ offset = {0.0f, 0.0f}; }
        virtual ~State(){};

        virtual void update(){};

        virtual void render(){
            for(Object *object : hTypes){ object->draw(offset); }
        };

    protected:
        SDL_FPoint offset;
    };
}
