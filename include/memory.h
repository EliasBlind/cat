#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

void *get_malloc(size_t length);
void *get_calloc(size_t item_size, size_t length);
void get_free(void *data);

#endif // MEMORY_H
