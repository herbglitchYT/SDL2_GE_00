#pragma once

#include "../entities/entity.hpp"
#include "../types/types.h"
#include "../ge.hpp"
#include <SDL.h>
#include <vector>
#include <stdint.h>

namespace ge {
    class QuadTree {
    public:
        QuadTree(GE_Bounds bounds): entity(nullptr), bounds(bounds){
            for(unsigned short i = 0; i < 4; i++){
                if(subdivisions[i]){ subdivisions[i] = nullptr; }
            }
        }

        ~QuadTree(){
            for(unsigned short i = 0; i < 4; i++){
                if(subdivisions[i]){ delete subdivisions[i]; }
            }
        }

        void render(){
            SDL_SetRenderDrawColor(ge::data->renderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderDrawRect(ge::data->renderer, &bounds);
            for(unsigned short i = 0; i < 4; i++){
                if(subdivisions[i]){ subdivisions[i]->render(); }
            }
        }

        void render(SDL_FPoint &offset){
            SDL_SetRenderDrawColor(ge::data->renderer, 0xff, 0xff, 0xff, 0xff);
            SDL_Rect temp = { bounds.x + (int)offset.x, bounds.y + (int)offset.y, bounds.w, bounds.h };
            SDL_RenderDrawRect(ge::data->renderer, &temp);
            for(unsigned short i = 0; i < 4; i++){
                if(subdivisions[i]){ subdivisions[i]->render(offset); }
            }
        }

        bool insert(Entity *entity){
            if(!pointInBounds(entity->getPos())){ return false; }

            if(!this->entity){
                this->entity = entity;
                return true;
            }

            subdivide(entity);
            return true;
        }

        bool remove(Entity *entity){
            if(!pointInBounds(entity->getPos())){ return false; }
        }

        void query(GE_Bounds *bounds, std::vector<Entity *> &entities){
            if(!SDL_HasIntersection(&this->bounds, bounds)){ return; }

            if(containsBounds(bounds)){
                query(entities);
                return;
            }

            entities.push_back(entity);
            for(unsigned short i = 0; i < 4; i++){
                if(subdivisions[i]){ subdivisions[i]->query(entities); }
            }
        }

        void query(std::vector<Entity *> &entities){
            entities.push_back(entity);
            for(unsigned short i = 0; i < 4; i++){
                if(subdivisions[i]){ subdivisions[i]->query(entities); }
            }
        }

        uint32_t height(){
            uint32_t max = 0, temp = 0;
            for(unsigned short i = 0; i < 4; i++){
                if(subdivisions[i]){
                    uint32_t h = subdivisions[i]->height();
                    temp = (h)? temp + h : 1;
                }
                max = (temp > max)? temp : max;
                temp = 0;
            }
            return max;
        }

    private:
        void subdivide(Entity *entity){
            if(entity->getPos().x <= (bounds.x + (bounds.w / 2)) && entity->getPos().y <= (bounds.y + (bounds.h / 2))){
                if(!subdivisions[0]){ subdivisions[0] = new QuadTree({ bounds.x, bounds.y, bounds.w / 2, bounds.h / 2 }); }
                subdivisions[0]->insert(entity);
                return;
            }

            if(entity->getPos().y <= (bounds.y + (bounds.h / 2))){
                if(!subdivisions[1]){ subdivisions[1] = new QuadTree({ bounds.x + bounds.w / 2, bounds.y, bounds.w / 2, bounds.h / 2 }); }
                subdivisions[1]->insert(entity);
                return;
            }

            if(entity->getPos().x <= (bounds.x + (bounds.w / 2))){
                if(!subdivisions[2]){ subdivisions[2] = new QuadTree({ bounds.x, bounds.y + bounds.h / 2, bounds.w / 2, bounds.h / 2 }); }
                subdivisions[2]->insert(entity);
                return;
            }

            if(!subdivisions[3]){ subdivisions[3] = new QuadTree({ bounds.x + bounds.w / 2, bounds.y + bounds.h / 2, bounds.w / 2, bounds.h / 2 }); }
            subdivisions[3]->insert(entity);
            return;
        }

        bool pointInBounds(SDL_FPoint &point){
            return (int)point.x >= bounds.x && (int)point.x <= bounds.x + bounds.w &&
                   (int)point.y >= bounds.y && (int)point.y <= bounds.y + bounds.h;
        }

        bool containsBounds(GE_Bounds *bounds){
            return bounds->x >= this->bounds.x && bounds->x + bounds->w <= this->bounds.x + this->bounds.w &&
                   bounds->y >= this->bounds.y && bounds->y + bounds->h <= this->bounds.y + this->bounds.h;
        }

        QuadTree *subdivisions[4];

        Entity *entity;

        GE_Bounds bounds;
    };
}