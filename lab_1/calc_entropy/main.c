#include <locale.h>
#include <wchar.h>
#include <stdio.h>

int main() {
    if (setlocale(LC_ALL, "ru_RU.utf8") == NULL ){
        fprintf(stderr, "Error: cant set locale\n");
        return 1;
    };

    // FILE *file = fopen("../TEXT.txt", "r");
    // if (NULL == file) {
    //     fprintf(stderr, "Cant open the file\n");
    //     return 1;
    // }
 

    // wint_t c;
    // while ((c = fgetwc(file)) != WEOF) {
    //     putwchar(c);
    // }

    // fclose(file);
    return 0;
}
