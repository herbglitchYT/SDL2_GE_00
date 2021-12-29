#pragma once

#include "state.hpp"
#include "../entities/entity.hpp"

namespace ge {
    class Surface : public State, public Handler<Entity> {
    public:
        Surface(): offset(nullptr){}
        virtual ~Surface(){};

        virtual void update(){};

        virtual void render(){
            for(Entity *entity : hTypes){ if(offset){ entity->render(*offset); } }
        };

    protected:
        SDL_FPoint *offset;
    };
}
