#ifndef READ_BUFFER_H
#define READ_BUFFER_H

#include <stddef.h>
#include <stdbool.h>
#include <wchar.h>

#define BUFFER_SIZE (1 * 1024)

bool read_buffer_wide(const char *filename, wchar_t *buffer, size_t *chars_read);

#endif // READ_BUFFER_H