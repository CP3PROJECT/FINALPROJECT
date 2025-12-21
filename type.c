#include "type.h"
#include <stdio.h>
#include <string.h>


void initializeTypes(Type Types[18]) {
    FILE *file = fopen("types.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open types.txt!\n");
        return;
    }

    for (int i = 0; i < 18; i++) {
        fscanf(file, "%s", Types[i].name);

        for (int j = 0; j < 18; j++) {
            strcpy(Types[i].effects[j].atkName, Types[i].name);
            fscanf(file, "%s %lf", Types[i].effects[j].defName, &Types[i].effects[j].multiplier);
        }
    }

    fclose(file);
}