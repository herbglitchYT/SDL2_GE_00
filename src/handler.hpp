#pragma once

#include <vector>

namespace ge {
    template <class HandlerType>
    class Handler {
    public:
        Handler(){}

        virtual ~Handler(){
            clean();
            clear();
        }

        virtual void update(){
            clean();
            for(HandlerType *hType : hTypes){ hType->update(); }
        }

        virtual void render(){ for(HandlerType *hType : hTypes){ hType->render(); } }

        void add(HandlerType *hType, bool removing = false){
            if(removing){ remove(); }
            hTypes.push_back(hType);
        }

        void remove(){
            if(hTypes.empty()){ return; }
            deleteQueue.push_back(hTypes.at(hTypes.size() - 1));
            hTypes.erase(hTypes.begin() + hTypes.size() - 1);
        }

        void remove(HandlerType *&hType){
            if(hTypes.empty()){ return; }
            for(unsigned int i = 0; i < hTypes.size(); i++){
                if(hTypes.at(i) == hType){
                    deleteQueue.push_back(hTypes.at(i));
                    hTypes.erase(hTypes.begin() + i);
                }
            }
        }

        void clean(){
            for(HandlerType *hType : deleteQueue){ delete hType; }
            deleteQueue.clear();
        }

        void clear(){
            for(HandlerType *hType : hTypes){ delete hType; }
            hTypes.clear();
        }

        int size(){ return hTypes.size(); }

    protected:
        std::vector<HandlerType *> hTypes;
        std::vector<HandlerType *> deleteQueue;
    };
}
