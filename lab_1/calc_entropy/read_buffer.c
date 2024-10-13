#include "read_buffer.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>

// bool read_buffer_wide(const char *filename, wchar_t *buffer, size_t *chars_read) {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         fwprintf(stderr, L"Error: Cannot open file %s for reading.\n", filename);
//         return false;
//     }

//     *chars_read = 0;
//     wint_t wc;
//     while (*chars_read < BUFFER_SIZE && (wc = fgetwc(file)) != WEOF) {
//         buffer[*chars_read] = (wchar_t)wc;
//         (*chars_read)++;
//     }

//     wprintf(L"%Ls\n", buffer);

//     fclose(file);
//     return true;
// }

bool read_buffer_wide(FILE *file, wchar_t *buffer, size_t *chars_read) {
    assert(file != NULL);

    *chars_read = 0;
    wint_t wc;
    while (*chars_read < BUFFER_SIZE && (wc = fgetwc(file)) != WEOF) {
        buffer[*chars_read] = (wchar_t)wc;
        (*chars_read)++;
    }
    return true;
}