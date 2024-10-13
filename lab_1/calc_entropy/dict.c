#include "dict.h"
#include <assert.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

static DictEntry *Dict_get_entry_by_key(Dict *dict, wchar_t *key) {
    int i;
    wchar_t *dkey;
    
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

    return dict;
}


bool Dict_exists_entry(Dict *dict, wchar_t *key) {
    DictEntry *dentry;
    dentry = Dict_get_entry_by_key(dict, key);
    return NULL != dentry;
}


void Dict_insert_entry(Dict *dict, wchar_t *key, int value) {
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

int Dict_calc_total(Dict *dict, TypeOfGram gram_type, bool include_space) {
    DictEntry dentry;
    int i;
    int total;
  
    for (i = 0, total = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];

        if (gram_type == MONOGRAM && wcslen(dentry.key) != 1) {
            continue;
        } else if (gram_type == BIGRAM && wcslen(dentry.key) != 2) {
            continue;
        }

        if (!include_space && (wcschr(dentry.key, L' ') != NULL)) {
            continue;
        }
    
        total += dentry.value;
    }

    return total;
}

static int cmp_dentries(const void *dentry_1, const void *dentry_2) {
    DictEntry *de1, *de2;
    de1 = (DictEntry *) dentry_1;
    de2 = (DictEntry *) dentry_2;

    return de2->value - de1->value;
}

void Dict_sort_by_desc(Dict *dict) {
    qsort(dict->dict_entries, dict->occupied, sizeof(DictEntry), &cmp_dentries);
}