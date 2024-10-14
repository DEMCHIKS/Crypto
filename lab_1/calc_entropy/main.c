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
    form_str_2 = L"";

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

void print_monogram_seq(Dict *dict, wchar_t *alph, PrintType ptype) {
    bool include_space;
    int i;
    int alph_len;
    wchar_t key[2];
    int numb_of_occur, total_number;
    float freq;

    key[1]= L'\0';
    include_space = wcschr(alph, L' ') != NULL;
    alph_len = wcslen(alph);
    total_number = Dict_calc_total(dict, MONOGRAM, include_space);


    for (i = 0; i < alph_len; ++i) {
        key[0] = alph[i];
        numb_of_occur = Dict_get_value(dict, &key[0]);

        if (ptype == OCCUR) {
            wprintf(L"[%lc] - %d\n", alph[i], numb_of_occur);
        } else if (ptype == FREQ) {
            freq = (float) numb_of_occur / total_number;
            wprintf(L"[%lc] - %.6f\n", alph[i], freq);
        }

    }

}

// }

int main() {
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL) {
        fwprintf(stderr, L"Error: can't set locale\n");
        return 1;
    }

    Dict *dict, *dict2;
    dict = Dict_INIT(ALPHABET);
    dict2 = Dict_INIT(ALPHABET);

    
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

    // 1) number of monogram occurences sorted by descending
    
    // monorams with spaces
    monogram(full_text, true, dict);
    Dict_sort_by_desc(dict);
    wprintf(L"Number of monogram occurences sorted by descending with spaces.\n");
    print_monogram_seq(dict, ALPHABET, OCCUR);
    //print_results(dict, true, MONOGRAM);

    // monogram without spaces
    wprintf(L"Number of monogram occurences sorted by descending without spaces.\n");
    print_monogram_seq(dict, ALPHABET + 1, OCCUR);
    //print_results(dict, false, MONOGRAM);

    // 2) number of bigram occurences - print as square matrix
    
    // =====================STEP 1========================(bigram)
    // indexed by first and second letters of bigram with spaces (step1)
    bigram(full_text, dict, true, 1);
    wprintf(L"\nTable of bigram with spaces.\n");
    print_bigram_table(dict, ALPHABET, OCCUR);
 
    // indexed by first and second letters of bigram without spaces (step1)
    wprintf(L"\nTable of bigram without spaces.\n");
    print_bigram_table(dict, ALPHABET + 1, OCCUR);


    // =====================STEP 2========================(bigram)
    // indexed by first and second letters of bigram with spaces (step2)
    bigram(full_text, dict2, true, 2);
    wprintf(L"\nTable of bigram with spaces.\n");
    print_bigram_table(dict2, ALPHABET, OCCUR);
 
    // indexed by first and second letters of bigram without spaces (step2)
    wprintf(L"\nTable of bigram without spaces.\n");
    print_bigram_table(dict2, ALPHABET + 1, OCCUR);

    // =====================ENTROPY=========================
    // 3-1)  h1 for monogram with spaces
    float entropy;
    entropy = H1_monogram_with_SPACE(dict);
    wprintf(L"\nEntropy for monograms with spaces: %f\n", entropy);
    // 3-2)  h1 for monogram without space
    entropy = H1_monogram_without_SPACE(dict);
    wprintf(L"\nEntropy for monograms without spaces: %f\n", entropy);
    
    // 4-1)  h2 for bigram with spaces (step 1)
    entropy = H2_bigram_with_SPACE(dict);
    wprintf(L"\nEntropy for bigrams with spaces -- STEP_1: %f\n", entropy);
    
    // 4-2)  h2 for bigram without spaces (step 1)
    entropy = H2_bigram_without_SPACE(dict);
    wprintf(L"\nEntropy for bigrams without spaces -- STEP_1: %f\n", entropy);
    
    // 4-3)  h2 for bigram with spaces (step 2)
    entropy = H2_bigram_with_SPACE(dict2);
    wprintf(L"\nEntropy for bigrams with spaces -- STEP_2: %f\n", entropy);
    
    // 4-4)  h2 for bigram without spaces (step 2)
    entropy = H2_bigram_without_SPACE(dict2);
    wprintf(L"\nEntropy for bigrams without spaces -- STEP_2: %f\n", entropy);

    // 5) freq monogram table sorted by descending
    // FREQ monograms with spaces
    wprintf(L"\nFrequencies of monograms sorted by descendig with spaces: \n");
    print_monogram_seq(dict, ALPHABET, FREQ);
    //print_results(dict, true, MONOGRAM);

    // FREQ monograms without spaces
    wprintf(L"Frequencies of monograms sorted by descendig without spaces: \n");
    print_monogram_seq(dict, ALPHABET + 1, FREQ);
    // print_results(dict, false, MONOGRAM);

    // 6) freq bigram table - print as square matrix
    // indexed by first and second letters of bigram
    wprintf(L"\nFrequencies bigrams table with spaces -- STEP - 1\n");
    print_bigram_table(dict, ALPHABET, FREQ);

    wprintf(L"\nFrequencies bigrams table without spaces -- STEP - 1\n");
    print_bigram_table(dict, ALPHABET + 1, FREQ);

    wprintf(L"\nFrequencies bigrams table with spaces -- STEP - 2\n");
    print_bigram_table(dict2, ALPHABET, FREQ);

    wprintf(L"\nFrequencies bigrams table without spaces -- STEP - 2\n");
    print_bigram_table(dict2, ALPHABET + 1, FREQ);
    
    Dict_destroy(dict);
    
    return 0;
}