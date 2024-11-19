#include"../include/memory.h"

#include "../include/input.h"
#include "../include/work_string.h"
#include <stdio.h>
#include <string.h>

String *read_line() {
    String *line = NewString();
    String *buffer = NewCustomString(256);
    while (fgets(buffer->text, buffer->_itemCount, stdin)) {
        AppendC(line, buffer->text);
        size_t new_lins = IndexOfC(line, "\n");
        if(new_lins != line->length) {
            RemoveEnd(line, line->length - new_lins);
            break;
        }
    }
    FreeString(buffer);
    return line;
}

String *read_fiel(String *fiel_name) {
    FILE *fiel = fopen(fiel_name->text, "r");
    String *result = NewString();
    char buffer[256];
    if(fiel) {
        while (fgets(buffer, sizeof(buffer), fiel)) {
            AppendC(result, buffer);
        }
        fclose(fiel);
    }
    return result;
}
