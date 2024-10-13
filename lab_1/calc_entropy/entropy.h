#ifndef ENTROPY_H
#define ENTROPY_H
#include "dict.h"

float calculate_entropy(Dict *dict, int total, int gram_size);
float H1_monogram_with_SPACE(Dict *dict);
float H1_monogram_without_SPACE(Dict *dict);
float H2_bigram_with_SPACE(Dict *dict);
float H2_bigram_without_SPACE(Dict *dict);
float H2_bigram_with_SPACE_step2(Dict *dict);
float H2_bigram_without_SPACE_step2(Dict *dict);

#endif 