#include"../include/memory.h"

#include "../include/input.h"
#include "../include/work_string.h"
#include <stdio.h>
#include <string.h>


String *read_fiel() {
    String *fiel_name = NewString();
    scanf("%[^\n]", fiel_name->text);
    FILE *fiel = fopen(fiel_name->text, "r");
    FreeString(fiel_name);
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

int main() {
    String *test = NewSetString("121211211111");
    Replase(test, "12", "RATATATATA");
    PrintString(test);
    FreeString(test);
    return 0;
};
