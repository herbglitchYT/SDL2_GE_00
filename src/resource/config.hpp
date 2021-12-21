#pragma once

#include <SDL.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include "spritesheet.hpp"
#include "sprite.hpp"

#define GE_VAR_STR(var) #var, var

namespace ge {
    struct Data;

    class Config {
    public:
        Config();
        Config(const char* path);
        ~Config();

        int load(const char* path);
        int unload(const char* path);

        void printGroups();

        Config &operator=(std::string path);
        Config &operator=(const char *path);
        Config &operator=(char *path);

        Config &operator+=(std::string path);
        Config &operator+=(const char *path);
        Config &operator+=(char *path);

        void get(std::string name, int   &var);
        void get(std::string name, float &var);

        void get(std::string name, char *&var);
        void get(std::string name, std::string &var);
        void get(std::string name, SDL_Texture *&var);
        void get(std::string name, ColorGrid &var);
        void get(std::string name, SDL_Rect &var);

        SpriteParams createSpriteParams(SDL_Texture *&texture, SpriteStrs strs);
        SpriteParams createSpriteParams(SDL_Texture *&texture, SpriteStrs strs, SDL_Point pos);

        bool setGroup(std::string name);

    private:
        struct Group {
            std::string name;
            std::map<std::string, std::string> data;

            Group(std::string name): name(name){}
        };

        Group *getGroup(std::string name);
        int removeGroup(Group *g);

        int manageGroups(const char* path, bool load);
        int manageGroups(std::string &data, std::string path, bool load);

        int comment(std::string &data, unsigned int &i, bool multi);
        int hash(std::string &data, unsigned int &i, std::string path);
        int group(std::string name, std::string &data);
        int ungroup(std::string name, std::string &data);

        std::vector<Group *> groups;
        Group *currGroup;
        Data *data;
    };
}

