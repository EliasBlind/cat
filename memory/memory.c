#include <stdlib.h>

void *get_malloc(size_t length) {
    void *buffer = malloc(length);
    while (buffer == NULL) {
        buffer = malloc(length);
    }
    return buffer;
}

void *get_calloc(size_t item_size, size_t length) {
    return  get_malloc(item_size * length);
}

void get_free(void *data) {
    if(data != NULL)
        free(data);
}
