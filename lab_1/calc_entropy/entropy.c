#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <assert.h>
#include "dict.h"

#define COUNT_LETTER 32

static int conv_gram_type_to_int(TypeOfGram gram_type) {
    switch (gram_type)
    {
    case MONOGRAM:
        return 1;
    case BIGRAM:
        return 2;
    default:
        return -1;
    }
}

float calculate_entropy(Dict *dict, int total, TypeOfGram gram_type, bool include_space) {
    float accum = 0.0f;
    DictEntry dentry;
    int gram_size;

    gram_size = conv_gram_type_to_int(gram_type);
    assert(gram_size != -1);
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];

        if (!include_space && (wcschr(dentry.key, L' ') != NULL)) {
            continue;
        }

        if (!((wcslen(dentry.key) == (size_t) gram_size) && dentry.value > 0)) {
            continue;
        }

        float P = (float)dentry.value / total;
        accum += (-1.0f / gram_size) * (P * log2f(P));
    }
    
    return accum;
}


float H1_monogram_with_SPACE(Dict *dict) {
    int total;
    total = Dict_calc_total(dict, MONOGRAM, true);
    return calculate_entropy(dict, total, MONOGRAM, true);
}


float H1_monogram_without_SPACE(Dict *dict) {
    int total;
    total = Dict_calc_total(dict, MONOGRAM, false);
    return calculate_entropy(dict, total, MONOGRAM, false);
}

float H2_bigram_with_SPACE(Dict *dict) {
    int total;
    total = Dict_calc_total(dict, BIGRAM, true);
    return calculate_entropy(dict, total, BIGRAM, true);
}


float H2_bigram_without_SPACE(Dict *dict) {
    int total;
    total = Dict_calc_total(dict, BIGRAM, false);
    return calculate_entropy(dict, total, BIGRAM, false);
}