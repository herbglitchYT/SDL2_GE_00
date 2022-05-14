#ifndef GE_CONFIG_TYPES_H_
#define GE_CONFIG_TYPES_H_

//types
#define GE_TYPE_NONE       0x00

#define GE_TYPE_UINT8_T    0x01
#define GE_TYPE_UINT16_T   0x02
#define GE_TYPE_UINT32_T   0x03

#define GE_TYPE_INT        0x04
#define GE_TYPE_FLOAT      0x05

#define GE_TYPE_SCALE      0x06
#define GE_TYPE_COLOR      0x07

#define GE_TYPE_SHEET      0x08
#define GE_TYPE_BOUNDS     0x09

#define GE_TYPE_TILE       0x0a
#define GE_TYPE_SPRITE     0x0b
#define GE_TYPE_COLOR_GRID 0x0c

//predefs
#define GE_PRE_DEF_INCLUDE 0x01
#define GE_PRE_DEF_COMMENT 0x02

typedef struct GE_TypeVoid {
    uint8_t id;
    void *data;
} GE_TypeVoid;

typedef struct GE_KeyVal {
    char *key;
    GE_TypeVoid *val;
} GE_KeyVal;

typedef struct GE_Keyword {
    const char *key;
    int (*get)(uint32_t *i, const char *path, char *data, GE_KeyVal **val);
} GE_Keyword;


struct GE_Keycmp {
    int operator()(char const *a, char const *b) const { return strcmp(a, b) < 0; }
};

#endif
