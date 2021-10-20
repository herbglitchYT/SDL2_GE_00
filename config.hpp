#pragma once

#include <SDL.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include "resource/spritesheet.hpp"

#define ge_var(var) get(#var, var)

namespace ge {
    class Config {
    public:
        Config(){}
        Config(SDL_Renderer *renderer): renderer(renderer){}
        Config(const char* path, SDL_Renderer *renderer): renderer(renderer){ load(path); }

        ~Config(){
            for(Group *group : groups){ delete group; }
        }

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
                if(data.at(i) == '#'){
                    if(hash(data, i, path)){ return 1; }
                }
            }

            data.erase(std::remove_if(data.begin(), data.end(), ::isspace), data.end());
            return group("", data);
        }

        void unload(const char* path){

        }

        void printGroups(){
            for(Group *group : groups){
                printf(">%s\n", group->name.c_str());
                for(auto &gmap : group->data){
                    printf("\t>%s=%s\n", gmap.first.c_str(), gmap.second.c_str());
                }
            }
        }

        Config &operator=(std::string path){
            setGroup(path);
            return *this;
        }

        Config &operator=(const char *path){
            setGroup(std::string(path));
            return *this;
        }

        Config &operator=(char *path){
            setGroup(std::string(path));
            return *this;
        }

        Config &operator+=(std::string path){
            load(path.c_str());
            return *this;
        }

        Config &operator+=(const char *path){
            load(path);
            return *this;
        }

        Config &operator+=(char *path){
            load((const char *)path);
            return *this;
        }

        void get(std::string name, int &var){ var = stoi(currGroup->data[name]); }
        void get(std::string name, std::string &var){ var = currGroup->data[name]; }

        void get(std::string name, SDL_Texture *&var){
            var = resource::spritesheet(renderer, currGroup->data[name].c_str());
        }

        void get(std::string name, SDL_Rect &var){
            std::string data = currGroup->data[name];
            var.x = stoi(data.substr(1, data.find_first_of(',')));
            data = data.substr(data.find_first_of(',') + 1);

            var.y = stoi(data.substr(0, data.find_first_of(',')));
            data = data.substr(data.find_first_of(',') + 1);

            var.w = stoi(data.substr(0, data.find_first_of(',')));
            data = data.substr(data.find_first_of(',') + 1);

            var.h = stoi(data.substr(0, data.find_first_of('}')));
        }

        bool setGroup(std::string name){
            currGroup = getGroup(name);
            return (bool) currGroup;
        }

    private:
        struct Group {
            std::string name;
            std::map<std::string, std::string> data;

            Group(std::string name): name(name){}
        };

        Group *getGroup(std::string name){
            for(Group *&group : groups){
                if(group->name == name){ return group; }
            }

            return nullptr;
        }

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
            data = data.substr(0, i) + data.substr(i + s, data.length());
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

        bool group(std::string name, std::string &data){
            Group *g = getGroup(name);
            bool exists = (bool)g;
            if(!exists){ g = new Group(name); }

            std::string temp;
            int ret = 0;

            while(data.size() > 0){
                if(data.at(0) == '}'){
                    data = data.substr(1, data.size() - 1);
                    if(!exists){ groups.push_back(g); }
                    return 0;
                }

                if(data.substr(0, 5) == "group"){
                    temp = data.substr(5, data.find_first_of('{') - 5);
                    data = data.substr(data.find_first_of('{') + 1, data.size() - 1);

                    ret = group(temp, data);
                    continue;
                }

                std::string var = data.substr(0, data.find_first_of('='));
                std::string val = data.substr(var.size() + 1, data.find_first_of(';') - (var.size() + 1));
                g->data[var] = val;

                if(var.size() + val.size() + 2 < data.size()){
                    data = data.substr(var.size() + val.size() + 2, data.size() - 1);
                    continue;
                }

                data = "";
            }

            if(g->data.size() && !exists){ groups.push_back(g); }
            else { delete g; }
            return ret;
        }

        std::vector<Group *> groups;
        Group *currGroup;
        SDL_Renderer *renderer;
    };
}
// const Uint8 *state = SDL_GetKeyboardState(nullptr);
// printf("Mouse button: %d %d %d\n", SDL_GetMouseState(nullptr, nullptr), state[SDL_SCANCODE_1], SDL_GetModState());

