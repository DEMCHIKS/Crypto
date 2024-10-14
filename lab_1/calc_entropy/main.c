#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "filter_text.h"
#include "read_buffer.h"
#include "calculateFREQ.h"
#include "dict.h"
#include "entropy.h"

// wchar_t ALPHABET[] = L" абвгдежзийклмнопрстуфхцчшщыьэюя";

// void print_bigram_table(Dict ) {

// }

int main() {

    // Тестова стрічка
    // wchar_t str[] = L"есть тексты на русском языке";
    
    // Dict *dict;
    // dict = Dict_INIT(ALPHABET);
    // wchar_t key[3];
    // key[2] = L'\0';

    // for (int i = 0; i < 32; ++i) {
    //     key[0] = ALPHABET[i];
    //     for (int j = 0; j < 32; ++j) {
    //         key[1] = ALPHABET[j];
    //         int rand_value = rand() % 500;
    //         for (int k = 0; k < rand_value; ++k) {
    //             Dict_inc_value(dict, &key[0]);
    //         }
    //     }
    // }

    // Dict_sort_by_desc(dict);
    // print_results(dict, true, ALL);
    
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
    wprintf(L"Зчитаний текст:\n%ls\n", full_text);
    free(full_text);

    // 1) number of monogram occurences sorted by descending
    
    // // monorams with spaces
    // monogram(full_text, true, dict);
    // //Dict_sort_by_desc(dict);
    // wprintf(L"Number of monogram occurences sorted by descending.\n");
    // //print_results(dict, true, MONOGRAM);

    // // 2) number of bigram occurences - print as square matrix
    // // indexed by first and second letters of bigram
    // bigram(full_text, dict, true, 1);
    // wprintf(L"Number of bigram occurences sorted by descending.\n");
    // // Dict_sort_by_desc(dict);
    // print_results(dict, true, BIGRAM);
    
    // print_bigram_table();

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
    
    
    // // Звільнення пам'яті
    // Dict_destroy(dict);
    
    return 0;
}