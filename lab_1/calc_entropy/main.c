#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "filter_text.h"
#include "read_buffer.h"
#include "calculateFREQ.h"
#include "dict.h"
#include "entropy.h"

enum e_print_type {
    FREQ, OCCUR,
};

typedef enum e_print_type PrintType;


wchar_t ALPHABET[] = L" абвгдежзийклмнопрстуфхцчшщыьэюя";

void print_nwchars(wchar_t ch, int num) {
    int i;
    for (i = 0; i < num; ++i) {
        putwchar(ch);
    }
}

void print_bigram_table(Dict *dict, const wchar_t *alph, PrintType ptype) {
    int i, j;
    int alph_len, form_str1_len, form_str2_len;
    wchar_t key[3];
    int num_of_occur;
    wchar_t *form_str_1, *form_str_2;
    bool include_space;
    int total_number;
    float freq;

   
    alph_len = wcslen(alph);
    key[2] = L'\0';
    form_str_1 = L"l\\l|";
    form_str1_len = wcslen(form_str_1);

    if (ptype == OCCUR) {
        form_str_2 = L"  %lc  |";
    } else if (ptype == FREQ) {
        form_str_2 = L"   %lc   |";
    }

    form_str2_len = wcslen(form_str_2) - 2;
    
    include_space = wcschr(alph, L' ') != NULL;
    total_number = Dict_calc_total(dict, BIGRAM, include_space);
    
    // print first line
    wprintf(form_str_1);
    for (i = 0; i < alph_len; ++i) {
        wprintf(form_str_2, alph[i]);
    }
    putwchar(L'\n');

    // second line
    print_nwchars(L'-', form_str2_len * alph_len + form_str1_len);
    putwchar(L'\n');
    
    
    for (i = 0; i < alph_len; ++i) {
        key[0] = alph[i];
        wprintf(L" %lc |", alph[i]);

        for (j = 0; j < alph_len; ++j) {
            key[1] = alph[j];
            num_of_occur = Dict_get_value(dict, key);

            if (ptype == OCCUR) {
                wprintf(L"%5d|", num_of_occur);
            } else if (ptype == FREQ) {
                freq = (float) num_of_occur / total_number;
                wprintf(L".%06d|",  (int) (freq * pow(10, 6)));
                //wprintf(L"%.6f|",freq);
            }
        }
        putwchar(L'\n');
        print_nwchars(L'-', form_str2_len * alph_len + form_str1_len);
        putwchar(L'\n');
    }


}

// }

int main() {
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL) {
        fwprintf(stderr, L"Error: can't set locale\n");
        return 1;
    }

    Dict *dict;
    dict = Dict_INIT(ALPHABET);


    
    const char *input_file = "TEXT.txt";
    const char *filtered_file = "filtered.txt";
    
    // Process the input file
    if (!process_text(input_file, filtered_file)) {
        fwprintf(stderr, L"Error processing the text\n");
        return 1;
    }

    // Читання тексту частинами по 1 кілобайту
    
    wchar_t *full_text = get_text_from_file(filtered_file);
    if (full_text == NULL) {

        fwprintf(stderr, L"Error: Failed to read text from file\n");
        return 1;
    }

    // full_text = L"  есть тексты на русском языкезыкезыке";
    // wprintf(L"Зчитаний текст:\n%ls\n", full_text);
    // free(full_text);

    // 1) number of monogram occurences sorted by descending
    
    // monorams with spaces
    monogram(full_text, true, dict);
    // Dict_sort_by_desc(dict);
    wprintf(L"Number of monogram occurences sorted by descending.\n");
    print_results(dict, true, MONOGRAM);

    // 2) number of bigram occurences - print as square matrix
    // indexed by first and second letters of bigram
    bigram(full_text, dict, true, 1);
    wprintf(L"Number of bigram occurences sorted by descending.\n");
    // Dict_sort_by_desc(dict);
    // print_results(dict, true, BIGRAM);
    
    print_bigram_table(dict, ALPHABET, OCCUR);
    print_bigram_table(dict, ALPHABET + 1, FREQ);


    // 3-1)  h1 for monogram without spaces
    // 3-2)  h1 for monogram with space

    // 4-1)  h2 for bigram without spaces (step 1)
    // 4-2)  h2 for bigram with spaces (step 1)
    // 4-3)  h2 for bigram without spaces (step 2)
    // 4-4)  h2 for bigram with spaces (step 2)


    // 5) freq monogram table sorted by descending
    // 6) freq bigram table - print as square matrix
    // indexed by first and second letters of bigram
    
    // wprintf(L"Total characters read: %zu\n", total_chars_read);
    // wprintf(L"Аналіз повного тексту:\n\n");
    
    
    Dict_destroy(dict);
    
    return 0;
}