#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "filter_text.h"
#include "read_buffer.h"
#include "calculateFREQ.h"
#include "dict.h"
#include "entropy.h"

#define MAX_TEXT_SIZE 1000000 // Максимальний розмір тексту (можна змінити за потребою)

wchar_t ALPHABET[] = L" абвгдежзийклмнопрстуфхцчшщыьэюя";


void print_bigram_table(Dict ) {

}

int main() {
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL) {
        fprintf(stderr, "Error: can't set locale\n");
        return 1;
    }

    // Тестова стрічка
    // wchar_t str[] = L"есть тексты на русском языке";
    
    Dict *dict;
    dict = Dict_INIT(ALPHABET);
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


    // Підготовка буфера для всього тексту
    wchar_t *full_text = malloc(sizeof(wchar_t) * MAX_TEXT_SIZE);
    if (full_text == NULL) {
        fwprintf(stderr, L"Error allocating memory for full text\n");
        return 1;
    }
    
    size_t total_chars_read = 0;
    
    // // Читання тексту частинами по 1 кілобайту
    while (1) {
        wchar_t buffer[BUFFER_SIZE + 1];  // +1 for null terminator
        size_t chars_read;

        if (!read_buffer_wide(filtered_file, buffer, &chars_read)) {
            fwprintf(stderr, L"Error reading from filtered file\n");
            free(full_text);
            return 1;
        }

        if (chars_read == 0) {
            break; // Досягнуто кінця файлу
        }

        // Копіювання прочитаного фрагменту в повний текст
        if (total_chars_read + chars_read < MAX_TEXT_SIZE) {
            wcsncpy(full_text + total_chars_read, buffer, chars_read);
            total_chars_read += chars_read;
        } else {
            fwprintf(stderr, L"Warning: Text is too long, truncating\n");
            break;
        }
    }

    full_text[total_chars_read] = L'\0'; // Null-термінатор в кінці повного тексту

    // full_text = L"  есть тексты на русском языкезыкезыке";
    
    // 1) number of monogram occurences sorted by descending
    
    // monorams with spaces
    // monogram(full_text, true, dict);
    // //Dict_sort_by_desc(dict);
    // wprintf(L"Number of monogram occurences sorted by descending.\n");
    // //print_results(dict, true, MONOGRAM);

    // // 2) number of bigram occurences - print as square matrix
    // // indexed by first and second letters of bigram
    // bigram(full_text, dict, true, 1);
    // wprintf(L"Number of bigram occurences sorted by descending.\n");
    //Dict_sort_by_desc(dict);
    //print_results(dict, true, BIGRAM);
    
    //print_bigram_table();

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
    
    
    // Звільнення пам'яті
    // free(full_text);
    Dict_destroy(dict);
    
    return 0;
}