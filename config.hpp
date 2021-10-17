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

            return load(data);
        }

        int load(std::string &data){ 
            for(unsigned int i = 0; i < data.length(); i++){
                if(data.at(i) == '/' && data.at(i + 1) == '/'){ comment(data, i); }
                if(data.at(i) == '/' && data.at(i + 1) == '*'){ comment(data, i, true); }
                if(data.at(i) == '#'){ hash(data, i); }
            }
        }

        void unload(const char* path){

        }

        template <class T>
        void get(std::string name, T &var){}

    private:
        void comment(std::string &data, unsigned int &i, bool multi = false){
            int s = 2;
            if(!multi){
                while((data.at(s - 1) != '\n') || s >= data.length()){ s++; }
            }
            else {
                while((data.at(s - 2) != '*') || (data.at(s - 1) != '/') || s >= data.length()){ s++; }
            }
            data = data.substr(0, i - 1).substr(s, data.length());
        }

        bool hash(std::string &data, unsigned int &i){
            int s = 1;
            while(data.at(i + s) != '\n' || data.at(i + s) != '#'){ s++; }

            std::string temp = data.substr(i + 1, s - i);
            i = s + i;
  
            if(temp.find(' ') == std::string::npos){ return 1; }
            std::string first = temp.substr(0, temp.find_first_of(' '));

            std::string second = temp.substr(temp.find_first_of(' ') + 1, temp.size() - 1); 
            second.erase(std::remove_if(second.begin(), second.end(), ::isspace), second.end());
            second = second.substr(1, second.size() - 2);

            if(first == "include"){ return load(second); }
            if(first == "group"  ){
                cData.push_back(std::pair<std::string, std::vector<std::string>>(second, std::vector<std::string>()));
            }
            return 0;
        }

        std::vector<std::pair<std::string, std::vector<std::string>>> cData;
    };
}
// const Uint8 *state = SDL_GetKeyboardState(nullptr);
// printf("Mouse button: %d %d %d\n", SDL_GetMouseState(nullptr, nullptr), state[SDL_SCANCODE_1], SDL_GetModState());

