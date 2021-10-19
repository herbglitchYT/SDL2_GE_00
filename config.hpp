#pragma once

#include <SDL.h>
#include <string>
#include <algorithm>
#include <type_traits>
#include <fstream>
#include <vector>

#define ge_var(var) get<decltype(var)>(var, #var)

namespace ge {
    class Config {
    public:
        Config(){}
        ~Config(){}

        int load(const char* path){
            std::ifstream file(path);
            if(!file.is_open()){ return 1; }

            std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            return load(data, std::string(path));
        }

        int load(std::string &data, std::string path){ 
            for(unsigned int i = 0; i < data.length(); i++){
                if(data.substr(i, 2) == "//"){ comment(data, i); }
                if(data.substr(i, 2) == "/*"){ comment(data, i, true); }
                if(data.at(i) == '#'){ hash(data, i, path); }
            }

            data.erase(std::remove_if(data.begin(), data.end(), ::isspace), data.end());

            // group("", )
        }

        void unload(const char* path){

        }

        template <class T>
        void get(std::string name, T &var){}

    private:
        struct Group {
            std::string name;
            std::vector<std::string> data;
        };
        
        void comment(std::string &data, unsigned int &i, bool multi = false){
            int s = 2;
            if(!multi){
                while((data.at(i + s - 1) != '\n') && (i + s < data.length())){ s++; }
            }
            else {
                while((data.substr(i + s - 2, 2) != "*/") && (i + s < data.length())){ s++; }
            }

            data = data.substr(0, i - 1) + data.substr(i + s, data.length());
        }

        bool hash(std::string &data, unsigned int &i, std::string path){
            int s = 1;
            while((data.at(i + s) != '\n') && (i + s < data.length())){ s++; }

            std::string temp = data.substr(i + 1, s - i);
            data = data.substr(0, i - 1) + data.substr(i + s, data.length());
            i = s + i;

            if(temp.find(' ') == std::string::npos){ return 1; }
            std::string first = temp.substr(0, temp.find_first_of(' '));

            if(first == "include"){
                std::string npath = path.substr(0, path.find_last_of("/") + 1);

                npath += temp.substr(temp.find_first_of('"') + 1, temp.find_last_of('"') - temp.find_first_of('"') - 1); 

                return load(npath.c_str());
            }

            return 1;
        }

        std::vector<Group> data;
    };
}
// const Uint8 *state = SDL_GetKeyboardState(nullptr);
// printf("Mouse button: %d %d %d\n", SDL_GetMouseState(nullptr, nullptr), state[SDL_SCANCODE_1], SDL_GetModState());

