#include "config.hpp"

//avoid circular reference
#include "../ge.hpp"

namespace ge {
    Config::Config(){}
    Config::Config(Data *data): data(data){}
    Config::Config(const char* path, Data *data): data(data){ load(path); }

    Config::~Config(){
        for(Group *group : groups){ delete group; }
    }

    int Config::load(const char* path){   return manageGroups(path, true);  }
    int Config::unload(const char* path){ return manageGroups(path, false); }

    void Config::printGroups(){
        for(Group *group : groups){
            printf(">%s\n", group->name.c_str());
            for(auto &gmap : group->data){
                printf("\t>%s=%s\n", gmap.first.c_str(), gmap.second.c_str());
            }
        }
    }

    Config &Config::operator=(std::string path){
        setGroup(path);
        return *this;
    }

    Config &Config::operator=(const char *path){
        setGroup(std::string(path));
        return *this;
    }

    Config &Config::operator=(char *path){
        setGroup(std::string(path));
        return *this;
    }

    Config &Config::operator+=(std::string path){
        load(path.c_str());
        return *this;
    }

    Config &Config::operator+=(const char *path){
        load(path);
        return *this;
    }

    Config &Config::operator+=(char *path){
        load((const char *)path);
        return *this;
    }

    void Config::get(std::string name, int &var){ var = stoi(currGroup->data[name]); }
    void Config::get(std::string name, std::string &var){ var = currGroup->data[name]; }

    void Config::get(std::string name, SDL_Texture *&var){
        var = Spritesheet::load(data, currGroup->data[name].c_str());
    }

    void Config::get(std::string name, SDL_Rect &var){
        std::string data = currGroup->data[name];
        var.x = stoi(data.substr(1, data.find_first_of(',')));
        data = data.substr(data.find_first_of(',') + 1);

        var.y = stoi(data.substr(0, data.find_first_of(',')));
        data = data.substr(data.find_first_of(',') + 1);

        var.w = stoi(data.substr(0, data.find_first_of(',')));
        data = data.substr(data.find_first_of(',') + 1);

        var.h = stoi(data.substr(0, data.find_first_of('}')));
    }

    bool Config::setGroup(std::string name){
        currGroup = getGroup(name);
        return (bool) currGroup;
    }

    Config::Group *Config::getGroup(std::string name){
        for(Group *&group : groups){
            if(group->name == name){ return group; }
        }

        return nullptr;
    }

    int Config::removeGroup(Group *g){
        for(unsigned int i = 0; i < groups.size(); i++){
            if(g == groups.at(i)){
                groups.erase(groups.begin() + i);
                delete g;
                return 0;
            }
        }
        return 1;
    }

    int Config::manageGroups(const char* path, bool load){
        std::ifstream file(path);
        if(!file.is_open()){ return 1; }

        std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        return manageGroups(data, std::string(path), load);
    }

    int Config::manageGroups(std::string &data, std::string path, bool load){
        for(unsigned int i = 0; i < data.length(); i++){
            if(data.substr(i, 2) == "//"){ comment(data, i, false); }
            if(data.substr(i, 2) == "/*"){ comment(data, i, true); }
            if(data.at(i) == '#'){
                if(hash(data, i, path)){ return 1; }
            }
        }

        data.erase(std::remove_if(data.begin(), data.end(), ::isspace), data.end());
        return (load)? group("", data) : ungroup("", data);
    }

    int Config::comment(std::string &data, unsigned int &i, bool multi){
        int s = 2;
        if(!multi){
            while((data.at(i + s - 1) != '\n') && (i + s < data.length())){ s++; }
        }
        else {
            while((data.substr(i + s - 2, 2) != "*/") && (i + s < data.length())){ s++; }
        }

        data = data.substr(0, i) + data.substr(i + s, data.length());
        i -= 2;
        return 0;
    }

    int Config::hash(std::string &data, unsigned int &i, std::string path){
        int s = 1;
        while((data.at(i + s) != '\n') && (i + s < data.length())){ s++; }

        std::string temp = data.substr(i + 1, s - i);
        data = data.substr(0, i) + data.substr(i + s, data.length());

        if(temp.find(' ') == std::string::npos){ return 1; }
        std::string first = temp.substr(0, temp.find_first_of(' '));

        i--;

        if(first == "include"){
            std::string npath = path.substr(0, path.find_last_of("/") + 1);

            npath += temp.substr(temp.find_first_of('"') + 1, temp.find_last_of('"') - temp.find_first_of('"') - 1); 
            return load(npath.c_str());
        }

        return 1;
    }

    int Config::group(std::string name, std::string &data){
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

            if(g->data.find(var) != g->data.end()){ return 2; }
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

    int Config::ungroup(std::string name, std::string &data){
        Group *g = getGroup(name);
        if(!g){ return 1; }

        std::string temp;
        int ret = 0;

        while(data.size() > 0){
            if(data.at(0) == '}'){
                data = data.substr(1, data.size() - 1);
                if(g->data.empty()){ return removeGroup(g); }
                return 0;
            }

            if(data.substr(0, 5) == "group"){
                temp = data.substr(5, data.find_first_of('{') - 5);
                data = data.substr(data.find_first_of('{') + 1, data.size() - 1);

                ret = ungroup(temp, data);
                continue;
            }

            std::string var = data.substr(0, data.find_first_of('='));
            std::string val = data.substr(var.size() + 1, data.find_first_of(';') - (var.size() + 1));

            if(g->data.find(var) == g->data.end()){ return 2; }
            g->data.erase(var);

            if(var.size() + val.size() + 2 < data.size()){
                data = data.substr(var.size() + val.size() + 2, data.size() - 1);
                continue;
            }

            data = "";
        }

        if(g->data.empty()){ return removeGroup(g); }
        return ret;
    }
}
