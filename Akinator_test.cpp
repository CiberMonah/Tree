#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
#include "Akinator.h"

int main () {
    FILE* df = nullptr;

    if((df = fopen("dump_akinator.txt", "w")) == nullptr) {
        printf("Dump file creating error\n");
    }

    menu("akinator.txt", df);

    fclose(df);

    return 0;
}