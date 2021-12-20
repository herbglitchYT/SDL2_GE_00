#pragma once

namespace ge {
    class State {
    public:
        virtual ~State(){};

        virtual void update() = 0;
        virtual void render() = 0;

    };
}
