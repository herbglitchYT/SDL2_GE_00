#ifndef GE_HPP
#define GE_HPP

#include <SDL.h>
#include <stdio.h>
#include "handler/state.hpp"
#include "handler/handler.hpp"
#include "input/mouse.hpp"
#include "input/keyboard.hpp"
#include "resource/resource.hpp"

#define GE_MAIN(initState, width, height, title) int main(int argc, char *argv[]){\
    int ret = GE::init(width, height, title); if(ret){ return ret;}\
    ge::data->state.add(new initState());\
    ret = GE::run(); if(ret){ return ret; } return GE::deinit(); }

namespace ge {
    struct Data {
        Handler<State> state;
        Config config;

        Mouse mouse;
        Keyboard keyboard;

        SDL_Window *window;
        SDL_Rect windowSize;

        SDL_Renderer *renderer;

        SDL_Event event;

        float scale = 8.0f;
        float dt;
    };

    extern Data *data;
}

class GE {
public:
    static int init(int width, int height, const char *title);
    static int deinit();

    static int run();
};

#endif // !GE_HPP
