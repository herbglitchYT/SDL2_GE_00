#ifndef GE_CONFIG_TYPES_H_
#define GE_CONFIG_TYPES_H_

//types
#define GE_Type_None      0x00

#define GE_Type_uint8_t   0x01
#define GE_Type_uint16_t  0x02
#define GE_Type_uint32_t  0x03

#define GE_Type_int       0x04
#define GE_Type_float     0x05

#define GE_Type_Scale     0x06
#define GE_Type_Color     0x07

#define GE_Type_Sheet     0x08
#define GE_Type_Bounds    0x09

#define GE_Type_Tile      0x0a
#define GE_Type_Sprite    0x0b
#define GE_Type_ColorGrid 0x0c

//predefs
#define GE_PreDef_include 0x01

typedef struct GE_KeyVal {
    char *key;
    void *val;
} GE_KeyVal;

typedef struct GE_Keyword {
    const char *key;
    int (*get)(uint32_t *i, const char *path, char *data, GE_KeyVal **val);
} GE_Keyword;

typedef struct GE_TypeVoid {
    uint8_t id;
    void *data;
} GE_TypeVoid;

struct GE_Keycmp {
    int operator()(char const *a, char const *b) const { return strcmp(a, b) < 0; }
};

#endif
