#pragma once

#include "state.hpp"
#include "../resource/sprite.hpp"

namespace ge {
    namespace state {
        class Flat : public State, public Handler<Sprite> {
        public:
            Flat(){ offset = {0.0f, 0.0f}; }
            virtual ~Flat(){};

            virtual void update(){};

            virtual void render(){
                for(Sprite *object : hTypes){ object->render(offset); }
            };

        protected:
            SDL_FPoint offset;
        };
    }
}
