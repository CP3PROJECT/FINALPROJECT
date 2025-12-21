#include "move.h"
#include <stdio.h>

void initializeMoves(Move Moves[486], Type Types[18]) {
    FILE *file = fopen("moves.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open moves.txt!\n");
        return;
    }

    char typeName[50];
    char categoryName[50];

    for (int i = 0; i < 486; i++) {
        fscanf(file, "%s %s %s %d", Moves[i].name, typeName, categoryName, &Moves[i].power);

        for (int j = 0; j < 18; j++) {
            if (strcmp(typeName, Types[j].name) == 0) {
                Moves[i].type = Types[j];
                break;
            }
        }

        if (strcmp(categoryName, "Special") == 0) {
            Moves[i].category = Special_attack;
        } else {
            Moves[i].category = Physical_attack;
        }
    }

    fclose(file);
}