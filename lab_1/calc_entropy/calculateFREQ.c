#include "calculateFREQ.h"
#include "dict.h"
#include <wctype.h>

#define LETTER_COUNT 32  // Розмір алфавіту, включаючи пробіл

// Функція для отримання індексу символу в нашому алфавіті
// static int get_char_index(wchar_t ch) {
//     if (ch == L' ') return ALPHABET_SIZE - 1;
//     if (ch >= L'а' && ch <  L'ъ') return ch - L'а';
//     if (ch >  L'ъ' && ch <= L'я') return ch - L'а' - 1;
//     return -1;
// }

// // Функція для виведення результатів аналізу
// static void print_results(int frequencies[], int total, bool is_monogram) {
//     for (int i = 0; i < ALPHABET_SIZE; i++) {
//         if (frequencies[i] > 0) {
//             if (i == ALPHABET_SIZE - 1) {
//                 wprintf(L"пробіл: %d (%.2f%%)\n", frequencies[i], (float)frequencies[i] / total * 100);
//             } else if (i < L'ъ' - L'а'){
//             	wprintf(L"%lc: %d (%.2f%%)\n", L'а' + i, frequencies[i], (float)frequencies[i] / total * 100);
//             } else {
//             	wprintf(L"%lc: %d (%.2f%%)\n", L'а' + i + 1, frequencies[i], (float)frequencies[i] / total * 100);
//             }
//         }
//     }
// }


void print_results(Dict *dict, int total, TypeOfGram gram_type) {     
	DictEntry dentry;
	for (int i = 0; i < dict->occupied; ++i) {
        dentry = dict->dict_entries[i];
        if (gram_type == MONOGRAM && wcslen(dentry.key) != 1) {
        	continue;
        } else if (gram_type == BIGRAM && wcslen(dentry.key) != 2) {
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

    int total_chars = 0;
    wchar_t key[2];
    key[1] = L'\0';

    for (int i = 0; input_text[i] != L'\0'; ++i) {
    	if (input_text[i] == L' ' && !include_space) {
    		continue;
    	} 
    	key[0] = input_text[i];
    	Dict_inc_value(dict, &key[0]);
    	total_chars++;
    }
    
    wprintf(L"Монограма %s:\n", include_space ? L"з пробілом" : L"без пробілу");
    print_results(dict, total_chars, MONOGRAM);
}


// static void monogram(const wchar_t *text, bool include_space) {
//     if (text == NULL) return;

//     int frequencies[ALPHABET_SIZE] = {0};
//     int total_chars = 0;
    
//     for (int i = 0; text[i] != L'\0'; i++) {
//         int index = get_char_index(text[i]);
//         if (index != -1 && (include_space || index != ALPHABET_SIZE - 1)) {
//             frequencies[index]++;
//             total_chars++;
//         }
//     }
    
//     wprintf(L"Монограма %s:\n", include_space ? L"з пробілом" : L"без пробілу");
//     print_results(frequencies, total_chars, true);
// }

// wchar_t index_to_char(int i) {
//    	if (i == ALPHABET_SIZE - 1) {
//    		return L' ';
//     } else if (i < L'ъ' - L'а') {
//     	return i + L'а'; 
//    	} else if (i >= L'ъ' - L'а') {
//    		return i + L'а' + 1;
//    	}
// }


// // Функція для аналізу біграм
// static void bigram(const wchar_t *text, bool include_space, int step) {
//     if (text == NULL) return;

//     int frequencies[ALPHABET_SIZE][ALPHABET_SIZE] = {0};
//     int total_bigrams = 0;
//     int len = wcslen(text);
    
//     for (int i = 0; i < len - step; i++) {
//         int index1 = get_char_index(text[i]);
//         int index2 = get_char_index(text[i + step]);
        
//         if (index1 != -1 && index2 != -1 && 
//             (include_space || (index1 != ALPHABET_SIZE - 1 && index2 != ALPHABET_SIZE - 1))) {
//             frequencies[index1][index2]++;
//             total_bigrams++;
//         }
//     }
    
//     wprintf(L"Біграма з кроком %d %s:\n", step, include_space ? L"з пробілом" : L"без пробілу");
//     for (int i = 0; i < ALPHABET_SIZE; i++) {
//         for (int j = 0; j < ALPHABET_SIZE; j++) {
//             if (frequencies[i][j] > 0) {
//             	wchar_t first = index_to_char(i);
//             	wchar_t second = index_to_char(j);
//                 wprintf(L"%lc%lc: %d (%.2f%%)\n", first, second, frequencies[i][j], 
//                         (float)frequencies[i][j] / total_bigrams * 100);
//            	}
//         }
//     }
// }


void bigram(const wchar_t *input_text, Dict *dict, bool include_space, int step) {
    if (input_text == NULL) {
    	return;
    }

    wchar_t key[3];
    key[2] = L'\0';
    int total_bigrams = 0;
    int len = wcslen(input_text);
    
    for (int i = 0; i < len - step; i++) {
    	key[0] = input_text[i];
    	key[1] = input_text[i+step];
        if (!include_space && (key[0] == L' ' || key[1] == L' ')) {
        	continue;
        } 
        Dict_inc_value(dict, &key[0]);
        total_bigrams++;
    }
    print_results(dict, total_bigrams, BIGRAM);
}

// // Реалізація функцій-обгорток
// void monogram_with_space(const wchar_t *text) {
//     monogram(text, true);
// }

// void monogram_without_space(const wchar_t *text) {
//     monogram(text, false);
// }

// void bigram_step1_with_space(const wchar_t *text) {
//     bigram(text, true, 1);
// }

// void bigram_step1_without_space(const wchar_t *text) {
//     bigram(text, false, 1);
// }

// void bigram_step2_with_space(const wchar_t *text) {
//     bigram(text, true, 2);
// }

// void bigram_step2_without_space(const wchar_t *text) {
//     bigram(text, false, 2);
// }