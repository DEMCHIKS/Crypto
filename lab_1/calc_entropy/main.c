#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include "filter_text.h"
#include "read_buffer.h"
#include "calculateFREQ.h"
#include "dict.h"

#define MAX_TEXT_SIZE 1000000 // Максимальний розмір тексту (можна змінити за потребою)

wchar_t ALPHABET[] = L" абвгдежзийклмнопрстуфхцчшщыьэюя";

int main() {
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL) {
        fprintf(stderr, "Error: can't set locale\n");
        return 1;
    }

    // Тестова стрічка
    wchar_t str[] = L"есть тексты на русском языке";
    Dict *dict;
    dict = Dict_INIT(ALPHABET);

    monogram(str, true, dict);
    bigram(str, dict, true, 1);


    // wprintf(L"Аналіз тестової стрічки: \"%ls\"\n\n", str);

    // monogram_with_space(str);
    // wprintf(L"\n");
    // monogram_without_space(str);
    // wprintf(L"\n");
    // bigram_step1_with_space(str);
    // wprintf(L"\n");
    // bigram_step1_without_space(str);
    // wprintf(L"\n");
    // bigram_step2_with_space(str);
    // wprintf(L"\n");
    // bigram_step2_without_space(str);
    // wprintf(L"\n");

    // const char *input_file = "TEXT.txt";
    // const char *filtered_file = "filtered.txt";
    
    // // Process the input file
    // if (!process_text(input_file, filtered_file)) {
    //     fwprintf(stderr, L"Error processing the text\n");
    //     return 1;
    // }
    
    // // Підготовка буфера для всього тексту
    // wchar_t *full_text = malloc(sizeof(wchar_t) * MAX_TEXT_SIZE);
    // if (full_text == NULL) {
    //     fwprintf(stderr, L"Error allocating memory for full text\n");
    //     return 1;
    // }
    
    // size_t total_chars_read = 0;
    
    // // Читання тексту частинами по 1 кілобайту
    // while (1) {
    //     wchar_t buffer[BUFFER_SIZE + 1];  // +1 for null terminator
    //     size_t chars_read;
    //     if (!read_buffer_wide(filtered_file, buffer, &chars_read)) {
    //         fwprintf(stderr, L"Error reading from filtered file\n");
    //         free(full_text);
    //         return 1;
    //     }
    //     if (chars_read == 0) {
    //         break; // Досягнуто кінця файлу
    //     }
    //     // Копіювання прочитаного фрагменту в повний текст
    //     if (total_chars_read + chars_read < MAX_TEXT_SIZE) {
    //         wcsncpy(full_text + total_chars_read, buffer, chars_read);
    //         total_chars_read += chars_read;
    //     } else {
    //         fwprintf(stderr, L"Warning: Text is too long, truncating\n");
    //         break;
    //     }
    // }
    // full_text[total_chars_read] = L'\0'; // Null-термінатор в кінці повного тексту
    
    // wprintf(L"Total characters read: %zu\n", total_chars_read);
    // wprintf(L"Аналіз повного тексту:\n\n");
    
    // // Виклик функцій для аналізу тексту
    // monogram_with_space(full_text);
    // wprintf(L"\n");
    // monogram_without_space(full_text);
    // wprintf(L"\n");
    // bigram_step1_with_space(full_text);
    // wprintf(L"\n");
    // bigram_step1_without_space(full_text);
    // wprintf(L"\n");
    // bigram_step2_with_space(full_text);
    // wprintf(L"\n");
    // bigram_step2_without_space(full_text);
    
    // // Звільнення пам'яті
    // free(full_text);
    return 0;
}