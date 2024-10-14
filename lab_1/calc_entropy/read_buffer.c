#include "read_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <wctype.h>

#define MAX_TEXT_SIZE 1000000  // 1 MB
#define BUFFER_SIZE 1024 // 1 KB

static wchar_t* read_wide_file(FILE* file, size_t* total_chars_read) {
    if (file == NULL || total_chars_read == NULL) {
        return NULL;
    }

    wchar_t* buffer = malloc(sizeof(wchar_t) * INITIAL_BUFFER_SIZE);
    if (buffer == NULL) {
        return NULL;
    }

    size_t buffer_size = INITIAL_BUFFER_SIZE;
    *total_chars_read = 0;

    while (1) {
        if (*total_chars_read >= buffer_size - 1) {
            buffer_size *= 2;
            wchar_t* new_buffer = realloc(buffer, sizeof(wchar_t) * buffer_size);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }

        wint_t wc = fgetwc(file);
        if (wc == WEOF) {
            if (ferror(file)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        buffer[(*total_chars_read)++] = (wchar_t)wc;
    }

    buffer[*total_chars_read] = L'\0';
    return buffer;
}

wchar_t* get_text_from_file(const char* filename) {
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL) {
        fwprintf(stderr, L"Error: can't set locale\n");
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fwprintf(stderr, L"Error: Cannot open file %s for reading.\n", filename);
        return NULL;
    }

    size_t total_chars_read;
    wchar_t* full_text = read_wide_file(file, &total_chars_read);

    if (full_text == NULL) {
        fwprintf(stderr, L"Error reading from file or allocating memory\n");
    } else if (total_chars_read >= MAX_TEXT_SIZE) {
        fwprintf(stderr, L"Warning: Text is too long, truncating\n");
        full_text[MAX_TEXT_SIZE - 1] = L'\0';
    }

    fclose(file);
    return full_text;
}

