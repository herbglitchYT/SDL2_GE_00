#pragma once

#include "state.hpp"
#include "../resource/sprite.hpp"

namespace ge {
    class Surface : public State, public Handler<Sprite> {
    public:
        Surface(): offset({0.0f, 0.0f}){}
        Surface(SDL_FPoint offset): offset(offset){}
        virtual ~Surface(){};

        virtual void update(){};

        virtual void render(){
            for(Sprite *object : hTypes){ object->render(offset); }
        };

    protected:
        SDL_FPoint offset;
    };
}
