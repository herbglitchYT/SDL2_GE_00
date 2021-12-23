#pragma once

#include <stdint.h>

namespace ge {
    typedef struct ColorGrid {
        uint32_t *colors;
        uint32_t w, h;
    } ColorGrid;
}