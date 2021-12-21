#pragma once

namespace ge {
    class Object {
    public:
        virtual ~Object(){};

        virtual void draw(SDL_FPoint &offset) = 0;

        virtual void update() = 0;
        virtual void render() = 0;
    };
}
