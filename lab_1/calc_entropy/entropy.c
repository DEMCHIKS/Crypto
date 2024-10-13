#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include "dict.h"

#define COUNT_LETTER 32

float calculate_entropy(Dict *dict, int total, int gram_size) {
    float accum = 0.0f;
    DictEntry dentry;
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (wcslen(dentry.key) == gram_size && dentry.value > 0) {
            float P = (float)dentry.value / total;
            accum += (-1.0f / gram_size) * (P * log2f(P));
        }
    }
    
    return accum;
}

float H1_monogram_with_SPACE(Dict *dict) {
    int total = 0;
    DictEntry dentry;
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (wcslen(dentry.key) == 1) {
            total += dentry.value;
        }
    }
    
    return calculate_entropy(dict, total, 1);
}

float H1_monogram_without_SPACE(Dict *dict) {
    int total = 0;
    DictEntry dentry;
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (wcslen(dentry.key) == 1 && dentry.key[0] != L' ') {
            total += dentry.value;
        }
    }
    
    return calculate_entropy(dict, total, 1);
}

float H2_bigram_with_SPACE(Dict *dict) {
    int total = 0;
    DictEntry dentry;
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (wcslen(dentry.key) == 2) {
            total += dentry.value;
        }
    }
    
    return calculate_entropy(dict, total, 2);
}

float H2_bigram_without_SPACE(Dict *dict) {
    int total = 0;
    DictEntry dentry;
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (wcslen(dentry.key) == 2 && dentry.key[0] != L' ' && dentry.key[1] != L' ') {
            total += dentry.value;
        }
    }
    
    return calculate_entropy(dict, total, 2);
}

float H2_bigram_with_SPACE_step2(Dict *dict) {
    int total = 0;
    DictEntry dentry;
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (wcslen(dentry.key) == 2) {
            total += dentry.value;
        }
    }
    
    return calculate_entropy(dict, total, 2);
}

float H2_bigram_without_SPACE_step2(Dict *dict) {
    int total = 0;
    DictEntry dentry;
    
    for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (wcslen(dentry.key) == 2 && dentry.key[0] != L' ' && dentry.key[1] != L' ') {
            total += dentry.value;
        }
    }
    
    return calculate_entropy(dict, total, 2);
}

// void calculate_and_print_entropies(Dict *dict) {
//     printf("H1 монограма з пробілом: %f\n", H1_monogram_with_SPACE(dict));
//     printf("H1 монограма без пробілу: %f\n", H1_monogram_without_SPACE(dict));
//     printf("H2 біграма з кроком 1 з пробілом: %f\n", H2_bigram_with_SPACE(dict));
//     printf("H2 біграма з кроком 1 без пробілу: %f\n", H2_bigram_without_SPACE(dict));
//     printf("H2 біграма з кроком 2 з пробілом: %f\n", H2_bigram_with_SPACE_step2(dict));
//     printf("H2 біграма з кроком 2 без пробілу: %f\n", H2_bigram_without_SPACE_step2(dict));
// }

// int main() {
//     wchar_t *alphabet = L" абвгґдеєжзиіїйклмнопрстуфхцчшщьюя";
//     Dict *dict = Dict_INIT(alphabet);
    
//     // Тут потрібно додати код для заповнення словника даними з тексту
//     // Використовуйте модифіковані функції monogram() та bigram() з файлу calculateFREQ.c
    
//     calculate_and_print_entropies(dict);
    
//     Dict_destroy(dict);
//     return 0;
// }