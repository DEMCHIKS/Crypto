#include "calculateFREQ.h"
#include "dict.h"
#include <wctype.h>

#define LETTER_COUNT 32  // Розмір алфавіту, включаючи пробіл

void print_results(Dict *dict, bool include_spaces, TypeOfGram gram_type) {    
	DictEntry dentry;

	for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        
        if (gram_type == MONOGRAM && wcslen(dentry.key) != 1) {
        	continue;
        } else if (gram_type == BIGRAM && wcslen(dentry.key) != 2) {
        	continue;
        }

        if (!include_spaces && (wcschr(dentry.key, L' ') != NULL)) {
            continue;
        }

        if (dentry.value > 0) {
	        wprintf(L"Key: [%ls]; Value: [%d]\n", dentry.key, dentry.value);
        }
    }
}

void monogram(const wchar_t *input_text, bool include_space, Dict *dict) {
    if (input_text == NULL) { 
    	return;
    }

    // int total_chars = 0;
    wchar_t key[2];
    key[1] = L'\0';

    for (int i = 0; input_text[i] != L'\0'; ++i) {
    	if (input_text[i] == L' ' && !include_space) {
    		continue;
    	} 
    	key[0] = input_text[i];
    	Dict_inc_value(dict, &key[0]);
    	// total_chars++;
    }
    
}

void bigram(const wchar_t *input_text, Dict *dict, bool include_space, int step) {
    if (input_text == NULL) {
    	return;
    }

    wchar_t key[3];
    key[2] = L'\0';
    int len = wcslen(input_text);
    
    for (int i = 0; i < (len - step + 1); i += step) {
    	key[0] = input_text[i];
    	key[1] = input_text[i + 1];
        if (!include_space && (key[0] == L' ' || key[1] == L' ')) {
        	continue;
        } 
        Dict_inc_value(dict, &key[0]);
    }
}
