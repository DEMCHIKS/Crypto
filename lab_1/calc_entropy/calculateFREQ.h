#ifndef CALCULATE_FREQ_H
#define CALCULATE_FREQ_H

#include <wchar.h>
#include "dict.h"

enum e_type_of_gram {
	MONOGRAM, BIGRAM, ALL
}; 

typedef enum e_type_of_gram TypeOfGram; 

void print_results(Dict *dict, int total, TypeOfGram gram_type);
void monogram(const wchar_t *input_text, bool include_space, Dict *dict);
void bigram(const wchar_t *input_text, Dict *dict, bool include_space, int step);

#endif 