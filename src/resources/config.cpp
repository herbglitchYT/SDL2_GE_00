#include "config.hpp"

#include "../ge.hpp"

namespace ge {
    Config::Config(const char *homePath): homePath((char *)homePath){
        keywordSize = 12;
        keywords = new GE_Keyword[keywordSize]{
            { "/",            &comment   },
            { "#",            &hash      },
            { "ColorGrid",    &colorGrid },
            { "Sheet",        &sheet     },
            { "Sprite",       &sprite    },
            { "uint",         &uintF     },
            { "int",          &intF      },
            { "float",        &floatF    },
            { "Scale",        &scale     },
            { "Color",        &color     },
            { "Bounds",       &bounds    },
            { "Tile",         &tile      }
        };
    }

    Config::~Config(){
        for(std::pair<const char *, Group *> group : groups){
            for(std::pair<const char *, GE_TypeVoid *> g : group.second->data){
                void *gdata = ((GE_TypeVoid *)g.second->data)->data;
                switch(g.second->id){
                    case GE_TYPE_SPRITE:
                        SDL_DestroyTexture((SDL_Texture *)((GE_Sprite *)gdata)->sheet);
                        delete ((GE_Sprite *)gdata)->bounds;
                        break;

                    case GE_TYPE_COLOR_GRID:
                        // delete[] ((GE_ColorGrid *)gdata)->colors;
                        // delete (GE_ColorGrid *)gdata;
                        break;

                    case GE_TYPE_SHEET:
                        SDL_DestroyTexture((SDL_Texture *)gdata);
                        break;

                    case GE_TYPE_UINT8_T : delete (uint8_t   *)gdata; break;
                    case GE_TYPE_UINT16_T: delete (uint16_t  *)gdata; break;
                    case GE_TYPE_UINT32_T: delete (uint32_t  *)gdata; break;
                    case GE_TYPE_INT     : delete (int       *)gdata; break;
                    case GE_TYPE_FLOAT   : delete (float     *)gdata; break;
                    case GE_TYPE_SCALE   : delete (GE_Scale  *)gdata; break;
                    case GE_TYPE_COLOR   : delete (GE_Color  *)gdata; break;
                    // case GE_TYPE_BOUNDS  : delete (GE_Bounds *)gdata; break;
                    case GE_TYPE_TILE    : delete (GE_Tile   *)gdata; break;
                    default:
                        delete (GE_TypeVoid *)g.second->data;
                        break;
                }
                delete g.second;
            }

            delete group.second;
        }
    }

    int Config::load(  const char* path){ return readFile(path, true ); }
    int Config::unload(const char* path){ return readFile(path, false); }

    void Config::get(const char *name, GE_Scale     *&var){ var = ((currGroup->data[name])->id == GE_TYPE_SCALE)     ? (GE_Scale     *)(currGroup->data[name])->data : nullptr; }
    void Config::get(const char *name, GE_Bounds    *&var){ var = ((currGroup->data[name])->id == GE_TYPE_BOUNDS)    ? (GE_Bounds    *)(currGroup->data[name])->data : nullptr; }
    void Config::get(const char *name, GE_Sprite    *&var){ var = ((currGroup->data[name])->id == GE_TYPE_SPRITE)    ? (GE_Sprite    *)(currGroup->data[name])->data : nullptr; }
    void Config::get(const char *name, GE_Sheet     *&var){ var = ((currGroup->data[name])->id == GE_TYPE_SHEET)     ? (GE_Sheet     *)(currGroup->data[name])->data : nullptr; }
    void Config::get(const char *name, GE_ColorGrid *&var){ var = ((currGroup->data[name])->id == GE_TYPE_COLOR_GRID)? (GE_ColorGrid *)(currGroup->data[name])->data : nullptr; }

    bool Config::setGroup(const char *name){
        currGroup = groups[name];
        return (bool) currGroup;
    }

    int Config::readFile(const char *path, bool load){
        FILE *file = fopen(path, "rb");
        if(!file){ return -1; }

        fseek(file, 0L, SEEK_END);
        long fSize = ftell(file);
        rewind(file);

        char *data = (char *) calloc(1, fSize + 1);
        if(!data){
            fclose(file);
            return -2;
        }

        if(1 != fread(data, fSize, 1, file)){
            fclose(file);
            return -3;
        }

        fclose(file);
        uint32_t i = 0;
        int err = parse(&i, data, load);
        free(data);

        return err;
    }

    int Config::handleKeyVal(Group *group, GE_KeyVal *kval, bool &load){
        if(((GE_TypeVoid *)kval->val)->id == GE_TYPE_NONE){
            if(((GE_TypeVoid *)(kval->val)->data)->id == GE_PRE_DEF_COMMENT){ return 0; }
            if(((GE_TypeVoid *)(kval->val)->data)->id == GE_PRE_DEF_INCLUDE){ return readFile((char *)((GE_TypeVoid *)((GE_TypeVoid *)kval->val)->data)->data, load); }
            return -4;
        }
        group->data[kval->key] = kval->val;
        return 0;
    }

    int Config::parse(uint32_t *i, char *data, bool load, char *groupName){
        Group *group = (groups.find(groupName) != groups.end())? groups[groupName] : new Group(groupName);

        while(*i < (uint32_t)strlen(data)){
            if(data[*i] == ' ' || data[*i] == '\n' || data[*i] == '\r' || data[*i] == '\t'){ ++*i; continue; }

            if(data[*i] == '}'){
                groups[groupName] = group;
                return 0;
            }

            if(strlen(data) > strlen("Group") && !strncmp("Group", data, strlen("Group"))){
                i += strlen("Group");
                uint32_t index;
                while(data[index + *i] != '{' && *i + index < strlen(data)){ i++; }
                if(data[index + *i] != '{'){ return -5; }

                char *group = new char [index];
                strncpy(group, (data + *i), index);
                group[index - 1] = '\0';
                *i += index;

                int err = parse(i, data, load, group);
                if(err){ return err; }
            }

            for(uint32_t index = 0; index < keywordSize; index++){
                if(strlen(data + *i) > strlen(keywords[index].key) && !strncmp(keywords[index].key, data + *i, strlen(keywords[index].key))){
                    GE_KeyVal *kval;
                    int err = keywords[index].get(i, homePath, data, &kval);
                    if(err){ return err; }

                    if(kval){
                        err = handleKeyVal(group, kval, load);
                        if(err){ return err; }
                        delete kval;
                    }

                    --*i;
                    break;
                }
            }

            ++*i;
        }

        groups[groupName] = group;
        return *i - strlen(data) - 1;
    }

    char *Config::url(char *homePath, char *path){
        if(path[0] == '~'){
            char *url = new char[strlen(homePath) + strlen(path) - 1];
            strncpy(url, homePath, strlen(homePath));
            strncpy(url + strlen(homePath), path + 2, strlen(path) - 1);
            return url;
        }
        
        char *url = new char[strlen(path) + 1];
        strcpy(url, path);
        
        return url;
    }

    int Config::find(char *data, uint32_t *len, char match){
        while(data[*len] != match && *len < strlen(data)){ ++*len; }
        if(data[*len] != match){ return -6; }
        return 0;
    }

    int Config::find(char *data, uint32_t *len, char *match){
        *len += strlen(match);
        while(strlen(data) > *len && strncmp(match, data + *len - strlen(match), strlen(match))){ ++*len; }
        if(strncmp(match, data + *len - strlen(match), strlen(match))){ return -7; }
        return 0;
    }

    int Config::strip(uint32_t *i, char *data, char match){
        uint32_t len = 0;
        int err = find(data + *i, &len, match);
        *i += len + 1;
        return err;
    }

    int Config::strip(uint32_t *i, char *data, char *match){
        uint32_t len = 0;
        int err = find(data + *i, i, match);
        *i += len + 1;
        return err;
    }

    int Config::strip(uint32_t *i, char *data, char **val, char match, bool removeMatch){
        uint32_t len = 0;
        int err = find(data + *i, &len, match);
        if(err){ return err; }

        len = (removeMatch)? len + 1 : len + 2;//add and extra for the \0 at the end of string
        *val = new char[len];
        strncpy(*val, (char *)(data + *i), len - 1);
        (*val)[len - 1] = '\0'; //de-reference then get val of string at len - 1
        *i += (removeMatch)? len : len - 1;

        return 0;
    }

    int Config::strip(uint32_t *i, char *data, char **val, char *match, bool removeMatch){
        uint32_t len = 0;
        int err = find(data + *i, &len, match);
        if(err){ return err; }
        if(removeMatch && len == 1){ return 0; }

        len++; //add and extra for the \0 at the end of string
        len = (removeMatch)? len - strlen(match) : len;
        *val = new char[len];
        strncpy(*val, (char *)(data + *i), len - 1);
        (*val)[len - 1] = '\0'; //de-reference then get val of string at len - 1
        *i += (removeMatch)? len + strlen(match) : len;

        return 0;
    }

    int Config::removeWhitespace(char **val){
        uint32_t start = 0, end = strlen(*val);
        while( (*val)[start]   == ' ' || (*val)[start  ] == '\t' || (*val)[start]   == '\r' || (*val)[start]   == '\n'){ start++; }
        while(((*val)[end - 1] == ' ' || (*val)[end - 1] == '\t' || (*val)[end - 1] == '\r' || (*val)[end - 1] == '\n') && start < end - 1){ end--; }
        if((int)end - (int)start < 0){ return -2000; }
        if(start == 0 && strlen(*val) == end){ return 0; }

        char *newVal = new char[(end - start) + 1];
        strncpy(newVal, start + *val, end - start);
        newVal[end - start] = '\0';

        delete [] *val;
        *val = newVal;

        return 0;
    }

    int Config::splitVar(uint32_t *i, char *data, char **utype, char **name, char **val){
        int err = strip(i, data, utype, ' ', true);
        if(err){ return err; }

        err = strip(i, data, name, '=', true);
        if(err){ return err; }

        err = strip(i, data, val, ';', true);
        return (err)? err : 0;
    }

    int Config::splitVar(uint32_t *i, char *data, char **name, char **val){
        int err = strip(i, data, ' ');
        if(err){ return err; }

        err = strip(i, data, name, '=', true);
        removeWhitespace(name);
        if(err){ return err; }

        err = strip(i, data, val, ';', true);
        removeWhitespace(val);
        return (err)? err : 0;
    }


    int Config::comment(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        int err = (data[++*i] == '/')? strip(i, data, '\n') : strip(i, data, (char *)"*/");
        if(err){ return err; }

        *val = new GE_KeyVal;
        (*val)->key = (char *)"";
        (*val)->val = new GE_TypeVoid { GE_TYPE_NONE, (void *) new GE_TypeVoid { GE_PRE_DEF_COMMENT, nullptr } };

        return 0;
    }

    int Config::hash(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        ++*i;
        if(strlen(data) > strlen("include") && !strncmp("include", data, strlen("include"))){
            int err = strip(i, data, '"');
            if(err){ return err; }

            char *includePath;
            err = strip(i, data, &includePath, '"', true);
            if(err){ return err; }

            err = strip(i, data, '\n');
            if(err){ return err; }

            *val = new GE_KeyVal;
            (*val)->key = (char *)"";
            (*val)->val = new GE_TypeVoid { GE_TYPE_NONE, (void *) new GE_TypeVoid { GE_PRE_DEF_INCLUDE, includePath } };

            return 0;
        }

        return -11;
    }

    int Config::uintF(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *utype, *name, *numstr;
        int err = splitVar(i, data, &utype, &name, &numstr);
        if(err){ return err; }

        long num = strtol(numstr, nullptr, 10);
        delete [] numstr;

        if(num < 0 || num >= 0x10000){
            delete [] utype;
            delete [] name;
            return -12;
        }

        *val = new GE_KeyVal;
        (*val)->key = name;

        if(strcmp(utype, "uint8_t")){
            delete [] utype;
            (*val)->val = new GE_TypeVoid { GE_TYPE_UINT8_T, (void *) new uint8_t((uint8_t)num) };
            return 0;
        }

        if(strcmp(utype, "uint16_t")){
            delete [] utype;
            (*val)->val = new GE_TypeVoid { GE_TYPE_UINT16_T, (void *) new uint8_t((uint8_t)num) };
            return 0;
        }

        if(strcmp(utype, "uint32_t")){
            delete [] utype;
            (*val)->val = new GE_TypeVoid { GE_TYPE_UINT32_T, (void *) new uint8_t((uint8_t)num) };
            return 0;
        }

        return -13;
    }

    int Config::intF(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *numstr;
        int err = splitVar(i, data, &name, &numstr);
        if(err){ return err; }

        long num = strtol(numstr, nullptr, 10);
        delete [] numstr;

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_INT, (void *) new int((int)num) };

        return 0;
    }

    int Config::floatF(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *numstr;
        int err = splitVar(i, data, &name, &numstr);
        if(err){ return err; }

        float num = strtof(numstr, nullptr);
        delete [] numstr;

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_FLOAT, (void *) new int(num) };

        return 0;
    }

    int Config::scale(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *numstr;
        int err = splitVar(i, data, &name, &numstr);
        if(err){ return err; }

        long num = strtol(numstr, nullptr, 10);
        delete [] numstr;

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_SCALE, (void *) new GE_Scale((GE_Scale)num) };

        return 0;
    }

    int Config::color(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *numstr;
        int err = splitVar(i, data, &name, &numstr);
        if(err){ return err; }

        long num = strtol(numstr, nullptr, 0);
        delete [] numstr;

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_COLOR, (void *) new GE_Color((GE_Color)num) };

        return 0;
    }

    int Config::sheet(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *vpath;
        int err = splitVar(i, data, &name, &vpath);
        if(err){ return err; }

        char *sheetPath = url((char *)path, vpath);
        delete [] vpath;

        GE_Sheet *sheet = Spritesheet::load(sheetPath);
        delete [] sheetPath;

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_SHEET, (void *) sheet };
        return (sheet)? 0 : -14;
    }

    int Config::bounds(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *numarr;
        int err = splitVar(i, data, &name, &numarr);
        if(err){ return err; }

        uint32_t numarrIndex = 0;

        err = strip(&numarrIndex, numarr, '{');
        if(err){ return err; }

        int x, y, w, h;
        sscanf(numarr, "{%d,%d,%d,%d}", &x, &y, &w, &h);

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_BOUNDS, (void *) new GE_Bounds { x, y, w, h } };

        return 0;
    }

    int Config::tile(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *numarr;
        int err = splitVar(i, data, &name, &numarr);
        if(err){ return err; }

        uint32_t numarrIndex = 0;

        err = strip(&numarrIndex, numarr, '{');
        if(err){ return err; }

        uint32_t w, h;
        sscanf(numarr, "{%d,%d}", &w, &h);

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_BOUNDS, (void *) new GE_Tile { w, h } };

        return 0;
    }

    int Config::sprite(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *spriteData;
        int err = splitVar(i, data, &name, &spriteData);
        if(err){ return err; }

        uint32_t spriteDataIndex = 0;
        err = strip(&spriteDataIndex, spriteData, '{');
        if(err){ return err; }

        char *sheetStr;
        err = strip(&spriteDataIndex, spriteData, &sheetStr, ',', true);
        if(err){ return err; }

        char *boundStr;
        err = strip(&spriteDataIndex, spriteData, &boundStr, '}', true);
        if(err){ return err; }

        delete [] spriteData;

        GE_Sheet *sheet;
        spriteDataIndex = 0;
        if(!find(sheetStr, &spriteDataIndex, '.')){
            char *sheetPath = url((char *)path, sheetStr + 1);
            sheet = Spritesheet::load(sheetPath);
        }
        else {
            sheet = nullptr;
        }
        delete [] sheetStr;

        GE_Bounds *bounds;
        spriteDataIndex = 0;
        if(!find(boundStr, &spriteDataIndex, ',')){
            int x, y, w, h;
            sscanf(boundStr, "{%d,%d,%d,%d}", &x, &y, &w, &h);
            bounds = new GE_Bounds { x, y, w, h };
        }
        else {
            bounds = nullptr;
        }
        delete [] boundStr;

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_SPRITE, (void *) new GE_Sprite { sheet, bounds } };

        return 0;
    }

    int Config::colorGrid(uint32_t *i, const char *path, char *data, GE_KeyVal **val){
        char *name, *vpath;
        int err = splitVar(i, data, &name, &vpath);
        if(err){ return err; }

        char *sheetPath = url((char *)path, vpath);
        delete [] vpath;

        GE_ColorGrid *colorGrid = Spritesheet::loadColorGrid(sheetPath);
        delete [] sheetPath;

        *val = new GE_KeyVal;
        (*val)->key = name;
        (*val)->val = new GE_TypeVoid { GE_TYPE_COLOR_GRID, (void *) colorGrid };

        return (sheet)? 0 : -14;
    }


    // int Config::ungroup(std::string name, std::string &data){
    //     Group *g = getGroup(name);
    //     if(!g){ return 1; }

    //     std::string temp;
    //     int ret = 0;

    //     while(data.size() > 0){
    //         if(data.at(0) == '}'){
    //             data = data.substr(1, data.size() - 1);
    //             if(g->data.empty()){ return removeGroup(g); }
    //             return 0;
    //         }

    //         if(data.substr(0, 5) == "group"){
    //             temp = data.substr(5, data.find_first_of('{') - 5);
    //             data = data.substr(data.find_first_of('{') + 1, data.size() - 1);

    //             ret = ungroup(temp, data);
    //             continue;
    //         }

    //         std::string var = data.substr(0, data.find_first_of('='));
    //         std::string val = data.substr(var.size() + 1, data.find_first_of(';') - (var.size() + 1));

    //         if(g->data.find(var) == g->data.end()){ return 2; }
    //         g->data.erase(var);

    //         if(var.size() + val.size() + 2 < data.size()){
    //             data = data.substr(var.size() + val.size() + 2, data.size() - 1);
    //             continue;
    //         }

    //         data = "";
    //     }

    //     if(g->data.empty()){ return removeGroup(g); }
    //     return ret;
    // }
}
