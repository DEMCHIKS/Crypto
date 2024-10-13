#ifndef ENTROPY_H
#define ENTROPY_H
#include "dict.h"

float calculate_entropy(Dict *dict, int total, TypeOfGram gram_type, bool include_space);
float H1_monogram_with_SPACE(Dict *dict);
float H1_monogram_without_SPACE(Dict *dict);
float H2_bigram_with_SPACE(Dict *dict);
float H2_bigram_without_SPACE(Dict *dict);

#endif 