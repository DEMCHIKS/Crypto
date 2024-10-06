#include "filter_text.h"

#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <wctype.h>
#include <wchar.h>


enum {
    BUFFER_SIZE = 1024,
};


static bool is_letter_russian(wint_t ch) {
    return ((ch >= 0x0410) && (ch <= 0x044F))
        || (ch == 0x0451) || (ch == 0x0401);
}

static wchar_t replace_special_russian(wchar_t ch) {
    switch (ch) {
    case 0x042A: case 0x044A: // hard sign -> soft sign
        return 0x044C;
    case 0x0401: case 0x0451: // letter `E and `e -> e
        return 0x0435;
    default:
        return ch;
    }

}

bool process_text(const char *input_file, const char *output_file) {
    FILE *infile, *outfile;
    wchar_t ws_buffer[BUFFER_SIZE + 1];
    wchar_t *wc_ptr;
    bool last_ch_was_space;

    ws_buffer[BUFFER_SIZE] = L'\0';
    
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL ) {
        fprintf(stderr, "Error: cant set locale\n");
        return 1;
    };

    infile = fopen(input_file, "r");
    if (NULL == infile) {
        fprintf(stderr, "Error: can not open the file %s for reading.\n", input_file);
        return false;
    }

    outfile = fopen(output_file, "w");
    if (NULL == outfile) {
        fclose(infile);

        fprintf(stderr, "Error: can not open the file %s for writing.\n", output_file);
        return false;
    } 

    last_ch_was_space = false;
    while (fgetws(ws_buffer, BUFFER_SIZE, infile) != NULL) {
        for (wc_ptr = ws_buffer; *wc_ptr; wc_ptr++) {
            if(is_letter_russian(*wc_ptr)) {

                fputwc(replace_special_russian(towlower(*wc_ptr)), outfile);
                last_ch_was_space = false;
            } else if (iswspace(*wc_ptr)) {
                if (!last_ch_was_space) {
                    fputwc(L' ', outfile);
                    last_ch_was_space = true;
                }
            }
        }
    }

    fclose(infile);
    fclose(outfile);

    return true;
}