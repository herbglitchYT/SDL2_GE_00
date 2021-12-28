#pragma once

#include <SDL.h>
#include <map>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "spritesheet.hpp"
#include "../entities/sprite.hpp"
#include "../types/config.h"
#include "../types/types.h"

#define GE_VAR_STR(var) #var, var

#define GE_CONFIG_HOME "./res/"

namespace ge {
    class Config {
    public:
        Config(const char *urlHome = "./res/");
        ~Config();

        int load(const char* path);
        int unload(const char* path);

        // void printGroups();

        // void get(std::string name, int       &var);
        // void get(std::string name, int      *&var);
        // void get(std::string name, float     &var);
        // void get(std::string name, float    *&var);
        // void get(std::string name, uint32_t  &var);
        // void get(std::string name, uint32_t *&var);

        // void get(std::string name, char *&var);
        // void get(std::string name, std::string &var);
        void get(const char *name, GE_Scale     *&var);
        void get(const char *name, GE_Bounds    *&var);
        void get(const char *name, GE_Sheet     *&var);
        void get(const char *name, GE_ColorGrid *&var);
        void get(const char *name, GE_Sprite    *&var);
        // void get(std::string name, GE_ColorGrid *&var);
        // void get(std::string name, SDL_Rect &var);
        // void get(std::string name, Sprite *&var);

        bool setGroup(const char *name);

    private:
        struct Group {
            const char *name;
            std::map<const char *, void *, GE_Keycmp> data;

            Group(const char *name): name(name){}
        };

        int removeGroup(Group *g);

        int readFile(const char *path, bool load);

        int handleKeyVal(Group *group, GE_KeyVal *kval, bool &load);

        int parse(uint32_t *i, char *data, bool load, char *groupName = (char *)"");

        static char *url(char *homePath, char *path);

        static int find(char *data, uint32_t *len, char match);
        static int find(char *data, uint32_t *len, char *match);

        static int strip(uint32_t *i, char *data, char  match);
        static int strip(uint32_t *i, char *data, char *match);
        static int strip(uint32_t *i, char *data, char **val, char  match, bool removeMatch = false);
        static int strip(uint32_t *i, char *data, char **val, char *match, bool removeMatch = false);

        static int removeWhitespace(char **val);

        static int splitVar(uint32_t *i, char *data, char **name, char **val);
        static int splitVar(uint32_t *i, char *data, char **utype, char **name, char **val);

        static int comment  (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int hash     (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int uintF    (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int intF     (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int floatF   (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int scale    (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int color    (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int sheet    (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int bounds   (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int tile     (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int sprite   (uint32_t *i, const char *path, char *data, GE_KeyVal **val);
        static int colorGrid(uint32_t *i, const char *path, char *data, GE_KeyVal **val);

        std::map<const char *, Group *, GE_Keycmp> groups;
        GE_Keyword *keywords;
        uint32_t keywordSize;

        Group *currGroup;
        char *homePath;
    };
}

