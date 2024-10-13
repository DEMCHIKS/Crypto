#ifndef CALCULATE_FREQ_H
#define CALCULATE_FREQ_H

#include <wchar.h>
#include "dict.h"

void print_results(Dict *dict, bool include_spaces, TypeOfGram gram_type);
void monogram(const wchar_t *input_text, bool include_space, Dict *dict);
void bigram(const wchar_t *input_text, Dict *dict, bool include_space, int step);

#endif 