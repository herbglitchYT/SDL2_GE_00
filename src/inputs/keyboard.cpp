#include "keyboard.hpp"

namespace ge {
    Keyboard::Keyboard(){
        for(unsigned int i = 0; i < 239; i++){ keyboard[i] = NONE; }
    }

    void Keyboard::update(SDL_Event &event){
        if(event.key.keysym.sym >= 239 || event.key.keysym.sym < 0){ return; }

        if(event.key.state == SDL_PRESSED){
            keyboard[event.key.keysym.sym] = PRESSED;
            return;
        }

        if(keyboard[event.key.keysym.sym] == State::PRESSED){
            keyboard[event.key.keysym.sym] = RELEASED;
            released.push(event.key.keysym.sym);
            return;
        }

        while(!released.empty()){
            keyboard[released.top()] = NONE;
            released.pop();
        }
    }

    bool Keyboard::getPress(  int key){ return keyboard[key] == State::PRESSED;  }
    bool Keyboard::getRelease(int key){ return keyboard[key] == State::RELEASED; }

    Keyboard::State Keyboard::operator[](int key){ return keyboard[key]; }
}