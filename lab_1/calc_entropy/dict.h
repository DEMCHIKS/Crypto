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

enum e_type_of_gram {
	MONOGRAM, BIGRAM, ALL
}; 

typedef enum e_type_of_gram TypeOfGram; 


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


// create dict and fill it with monograms and bigramms
// argument - string with all charactes of target alphabet
Dict *Dict_INIT(wchar_t *alphabet);

// increment value by key
void Dict_inc_value(Dict *dict, wchar_t *key);
int Dict_calc_total(Dict *dict, TypeOfGram gram_type, bool include_space);


// sort dictionary in decsending order
void Dict_sort_by_desc(Dict *dict);

#endif