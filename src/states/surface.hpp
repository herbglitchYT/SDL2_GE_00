#pragma once

#include "state.hpp"
#include "../entities/entity.hpp"

namespace ge {
    class Surface : public State, public Handler<Entity> {
    public:
        Surface(): offset({0.0f, 0.0f}){}
        Surface(SDL_FPoint offset): offset(offset){}
        virtual ~Surface(){};

        virtual void update(){};

        virtual void render(){
            for(Entity *entity : hTypes){ entity->render(offset); }
        };

    protected:
        SDL_FPoint offset;
    };
}
