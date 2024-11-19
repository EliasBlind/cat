#include "include/work_string.h"
#include <stdio.h>
#include <string.h>



int main() {
    String *data = NewSetString("Hello world!");
    printf("Test\n");
    Replase(data, "llo", "");
    printf("Error. Data len  == %d, real len == %d\n", data->length, strlen(data->text));
    PrintString(data);
    FreeString(data);
    return 0;
}
