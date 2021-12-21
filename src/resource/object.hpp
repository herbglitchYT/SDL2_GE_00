#pragma once

namespace ge {
    class Object {
    public:
        virtual ~Object(){};

        virtual void draw(SDL_FPoint &offset) = 0;
    };
}
