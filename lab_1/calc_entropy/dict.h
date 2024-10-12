#ifndef DICT_H
#define DICT_H

#include <wchar.h>
#include <stdbool.h>

enum {
    DICT_VALUE_NOT_FOUND = -1,
};

struct s_dict_entry {
    wchar_t     *key;
    int         value;
};

typedef struct s_dict_entry DictEntry;

struct s_dict {
    DictEntry   *dict_entries;
    int         occupied;
    int         size;
};

typedef struct s_dict Dict;


// Create new dictionary: allocate memory for it
// it uses calloc: fill allocated memory with zeros
Dict *Dict_create(int size);


// Check if entry with such key exists in dictionary:
// if yes - returns true; if no - false
bool Dict_exists_entry(Dict *dict, wchar_t *key);


// If the entry exist in the dictionary, then it will change
// old entry's value with new one;
// Else: it will add new entry in dictionary
void Dict_insert_entry(Dict *dict, wchar_t *key, int value);


// Return value which corresponds the key:
// if entry wich such key does not exitst then returns DICT_VALUE_NOT_EXIST
int Dict_get_value(Dict *dict, wchar_t *key);

// Returns true if empty and false otherwise
bool Dict_is_empty(Dict *dict);

// Returns true if full and false otherwise
bool Dict_is_full(Dict *dict);


// Free memory from dictionary (including created wstrings) 
void Dict_destroy(Dict *dict);

// 
// IDEA for saving number of occurences letters and bigrams with the dictionary
// b1 = str[i];
// b2 = str[i + 1];
// wchar_t *bigr = malloc(sizeof(wchar_t) * (2 + 1))
// bigr[2] = L'\0'
// bigr[0] = b1
// bigr[1] = b2
// if (Dict_exists_entry(dict, bigr)) {
//     int bigr_count = Dict_get_value(dict, bigr);
//     Dict_insert_entry(dict, bigr, bigr_count + 1);
//     free(bigr);
// } else {
//     Dict_insert_entry(dict, bigr, 1)
// }
//

// create dict and fill it with monograms and bigramms
// argument - string with all charactes of target alphabet
Dict *Dict_INIT(wchar_t *alphabet);

// increment value by key
void Dict_inc_value(Dict *dict, wchar_t *key);

#endif