#pragma once

#include <SDL.h>
#include <string>
#include <type_traits>
#include <fstream>

#define ge_var(var) get<decltype(var)>(var, #var)

namespace ge {
    class Config {
    public:
        Config(){}
        ~Config(){}

        int load(const char* path){
            ifstream file(path);
            if(!file.is_open()){ return 1; }

            std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

            for(unsigned int i = 0; i < data.length(); i++){
                if(data.at(i) == '_' && data.at(i + 1) == '_'){ doubleUnder(data, i); }
            }
        }

        int load(std::string &data)

        void unload(const char* path){

        }

        template <class T>
        void get(std::string name, T &var){}

    private:
        void doubleUnder(std::string &data, unsigned int &i){
            i += 2;
            while((data.at(i) != '_' || data.at(i + 1) != '_') && i < data.length()){ i++; }
        }

        void openCurly(std::string &data, unsigned int &i, std::string &precursor){
            
        }
    };
}

// const Uint8 *state = SDL_GetKeyboardState(nullptr);
// printf("Mouse button: %d %d %d\n", SDL_GetMouseState(nullptr, nullptr), state[SDL_SCANCODE_1], SDL_GetModState());

