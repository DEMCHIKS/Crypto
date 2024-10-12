#include "dict.h"
#include <assert.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

static DictEntry *Dict_get_entry_by_key(Dict *dict, wchar_t *key) {
    int i;
    wchar_t *dkey;
    int key_len;
    
    for (i = 0; i < dict->occupied; ++i) {
        dkey = dict->dict_entries[i].key;
        if (wcscmp(dkey, key) == 0) {
            return dict->dict_entries + i;
        }
    }

    return NULL;
}

Dict *Dict_create(int size) {
    Dict *dict;
    
    assert(size > 0);
    dict = (Dict *) malloc(sizeof(Dict));
    dict->dict_entries = (DictEntry *) calloc(size, sizeof(DictEntry));
    dict->size = size;
    dict->occupied = 0;
}


bool Dict_exists_entry(Dict *dict, wchar_t *key) {
    DictEntry *dentry;
    dentry = Dict_get_entry_by_key(dict, key);
    return NULL != dentry;
}


void Dict_insert_entry(Dict *dict, wchar_t *key, int value) {
    int i;
    wchar_t *dkey;
    DictEntry *dentry;
    int key_len;
    
    dentry = Dict_get_entry_by_key(dict, key);


    if (NULL != dentry) {
        dentry->value = value;
        return;
    }

    assert(!Dict_is_full(dict));

    key_len = wcslen(key);
    dkey = (wchar_t *) malloc(sizeof(wchar_t) * key_len);
    wcsncpy(dkey, key, key_len); 
    dict->dict_entries[dict->occupied].key = dkey;
    dict->dict_entries[dict->occupied].value = value;
    dict->occupied++;
}


int Dict_get_value(Dict *dict, wchar_t *key) {
    int i;
    DictEntry *dentry;

    assert(!Dict_is_empty(dict));

    for (i = 0; i < dict->occupied; ++i) {
        dentry = Dict_get_entry_by_key(dict, key);
        if (NULL != dentry) {
            return dentry->value;
        } else {
            return DICT_VALUE_NOT_FOUND;
        }
    }

    // NO
    return DICT_VALUE_NOT_FOUND;
}


bool Dict_is_empty(Dict *dict) {
    return dict->occupied == 0;
}


bool Dict_is_full(Dict *dict) {
    return dict->size == dict->occupied;
}


// Free memory from dictionary (including created wstrings) 
void Dict_destroy(Dict *dict) {
    int i;
    DictEntry *dentry;

    for (i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries + i;
        if (NULL != dentry->key) {
            free(dentry->key);
        }
    }
    free(dict->dict_entries);
    free(dict);
}

// create dict and fill it with monograms and bigramms
// 32 + 32 * 32 - size
Dict *Dict_INIT(wchar_t *alphabet) {
    Dict *dict;
    wchar_t key[3];
    int i, j;
    int alphabet_len;

    alphabet_len = wcslen(alphabet);
    dict = Dict_create(alphabet_len + alphabet_len * alphabet_len);

    key[1] = L'\0';
    for (i = 0; i < alphabet_len; ++i) {
        key[0] = alphabet[i];
        Dict_insert_entry(dict, &key[0], 0);
    }

    key[2] = L'\0';
    for (i = 0; i < alphabet_len; ++i) {
        key[0] = alphabet[i];
        for (j = 0; j < alphabet_len; ++j) {
            key[1] = alphabet[j];
            Dict_insert_entry(dict, &key[0], 0);
        }
    }

    return dict;
}

// increment value by key
void Dict_inc_value(Dict *dict, wchar_t *key) {
    int val;
    assert(Dict_exists_entry(dict, key));
    
    val = Dict_get_value(dict, key);
    Dict_insert_entry(dict, key, val + 1);
}


// int main() {
//     Dict *dict;
//     int i;
//     DictEntry dentry;
    // dict = Dict_create(5);

    // Dict_insert_entry(dict, L"hello", 10);
    // Dict_insert_entry(dict, L"blabla2", 3);

    // printf("entry 1: %d\n", Dict_get_value(dict, L"hello"));
    // printf("entry 2: %d\n", Dict_get_value(dict, L"blabla2"));

    // Dict_insert_entry(dict, L"hello", 1);
    // Dict_insert_entry(dict, L"blabla2", 100);
    // Dict_insert_entry(dict, L"blabla3", 20);
    // Dict_insert_entry(dict, L"blabla4", 30);
    // Dict_insert_entry(dict, L"blabla5", 40);

    // printf("entry 1: %d\n", Dict_get_value(dict, L"hello"));
    // printf("entry 2: %d\n", Dict_get_value(dict, L"blabla2"));
    // printf("entry 3: %d\n", Dict_get_value(dict, L"blabla3"));
    // printf("entry 4: %d\n", Dict_get_value(dict, L"blabla4"));
    // printf("entry 5: %d\n", Dict_get_value(dict, L"blabla5"));

//     dict = Dict_INIT(L" abcdefgh");
//     for (i = 0; i < dict->occupied; ++i) {
//         dentry = dict->dict_entries[i];
//         wprintf(L"Key: [%ls]; Value: [%d]\n", dentry.key, dentry.value);
//     }

//     Dict_inc_value(dict, L"a");
//     Dict_inc_value(dict, L"a");

//     Dict_inc_value(dict, L"b");
    
//     Dict_inc_value(dict, L"c");
//     Dict_inc_value(dict, L"c");
//     Dict_inc_value(dict, L"c");

//     Dict_inc_value(dict, L"g");

//     Dict_inc_value(dict, L"a ");
//     Dict_inc_value(dict, L"a ");
//     Dict_inc_value(dict, L"gg");
//     Dict_inc_value(dict, L"ab");
//     Dict_inc_value(dict, L"ab");
//     Dict_inc_value(dict, L"ab");
//     Dict_inc_value(dict, L"ba");
//     Dict_inc_value(dict, L"ba");

//     for (i = 0; i < dict->occupied; ++i) {
//         dentry = dict->dict_entries[i];
//         wprintf(L"Key: [%ls]; Value: [%d]\n", dentry.key, dentry.value);
//     }

//     Dict_destroy(dict);
//     return 0;
// }