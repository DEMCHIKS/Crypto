#include "dict.h"

#include <wchar.h>
#include <stdlib.h>
#include <assert.h>

Dict *Dict_create(uint32 size) {
    assert(size > 0 && "Negative size of dictionary");

    Dict *dict = (Dict *) malloc(sizeof(Dict));
    dict->keys = (dict_key_t *) malloc(sizeof(dict_key_t) * size);
    dict->values = (dict_value_t *) malloc(sizeof(dict_value_t) * size);
    dict->size = size;
    dict->occupied = 0;

    return dict;
}


void Dict_destroy(Dict *dict) {
    assert(NULL != dict);
    
    free(dict->keys);
    free(dict->values);
    free(dict);
}


dict_value_t Dict_get(Dict *dict, dict_key_t key) {
    int i;

    for (i = 0; i < dict->size; ++i) {
        if(wcsstr(key, dict->keys[i])) {
            return dict->values[i];
        }
    }

    return VALUE_NOT_EXIST;
} 


void Dict_insert(Dict *dict, dict_key_t key, dict_value_t value) {
    assert(Dict_is_full(dict));
    
    dict->keys[dict->occupied] = key;
    dict->values[dict->occupied] = value;
    dict->occupied++;
}

//??????
void Dict_remove(Dict dict, dict_key_t key) {

}


bool Dict_is_empty(Dict *dict) {
    return dict->occupied == dict->size;
}


bool Dict_is_full(Dict *dict) {
    return dict->occupied == 0;
}