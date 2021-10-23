#ifndef GE_OBJECT_HPP
#define GE_OBJECT_HPP

#include "ge.hpp"

namespace ge {
    class Object {
    public:
        Object(unsigned int id = 0): id(id){}
        virtual ~Object(){ };

        virtual void update() = 0;
        virtual void render() = 0;

        unsigned int getId(){ return id; }

    protected:
        unsigned int id;
    };
}

#endif // !GE_OBJECT_HPP
