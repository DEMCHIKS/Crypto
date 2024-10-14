#ifndef READ_BUFFER_H
#define READ_BUFFER_H

#include <stddef.h>
#include <stdbool.h>
#include <wchar.h>

#define BUFFER_SIZE (1 * 1024)

wchar_t *get_text_from_file(const char *filename);

#endif // READ_BUFFER_H