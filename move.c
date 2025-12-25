#include "move.h"
#include <stdio.h>
#include <string.h>

void initializeMoves(Move Moves[], Type Types[]) {
    FILE *file = fopen("moves.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open moves.txt!\n");
        return;
    }

    char typeName[50];
    char categoryName[50];
    double tempPower;

    for (int i = 0; i < 486; i++) {
        fscanf(file, "%s %s %s %lf", Moves[i].name, typeName, categoryName, &tempPower);
        Moves[i].power = (int)tempPower;

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