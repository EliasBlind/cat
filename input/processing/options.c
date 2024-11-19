#include "../../include/work_string.h"
#include "../../include/input.h"
#include <stdio.h>

String *get_options(String *data) {
    printf("start ============================================================================================\n");
    size_t start = 0;
    String *answer = NewCustomString(data->length);
    while (start < data->length) {
        start = IndexOfC(data, "-");
        size_t end = start;
        while (data->text[end] != ' ' && end < data->length) end++;
        printf("end == %d, len == %d\n", end, data->length);
        String *buffer = GetSubstring(data, start, end);
        printf("buffer == ");
        PrintString(buffer);
        Append(answer, buffer);
        FreeString(buffer);
        RemoveAt(data, end - start, start);

        printf("    start for ===========================================================================================\n");

        size_t st = end - start;
        printf("        data : start == %d, end == %d, res == %d | data len == %d\n", start, end, st, data->length);
        for(int i = start; i < end; i++) {
            printf("%c", data->text[i]);
        }
        printf("\n");
        printf("    end for ============================================================================================\n");
        printf("result == ");
        PrintString(data);
    }
    Replase(answer, "-", "");
    printf("end ============================================================================================\n");
    return answer;
}

int main() {
    String *data = read_line();
    String *options = get_options(data);

    PrintString(data);
    PrintString(options);

    FreeString(data);
    FreeString(options);
    return 0;
}
