#ifndef DICT_H
#define DICT_H

#include <wchar.h>
#include <stdbool.h>

typedef unsigned int uint32;
typedef wchar_t * dict_key_t;
typedef uint32 dict_value_t;

enum {
    VALUE_NOT_EXIST = -1,
};

struct s_dict {
    dict_key_t      *keys;
    dict_value_t    *values;

    uint32          occupied;
    uint32          size;
};


typedef struct s_dict Dict;

Dict *Dict_create(uint32 size);
void Dict_destroy(Dict *dict);

dict_value_t Dict_get(Dict *dict, dict_key_t key);
void Dict_insert(Dict *dict, dict_key_t key, dict_value_t value);
void Dict_remove(Dict *dict, dict_key_t key);

bool Dict_is_empty(Dict *dict);
bool Dict_is_full(Dict *dict);


#endif