#include "type.h"
#include <stdio.h>
#include <string.h>


void initializeTypes(Type Types[]) {
    // Open the file
    FILE *file = fopen("types.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open types.txt!\n");
        return;
    }

    // Read 18 types
    for (int i = 0; i < 18; i++) {
        fscanf(file, "%s", Types[i].name);

        for (int j = 0; j < 18; j++) {
            strcpy(Types[i].effects[j].atkName, Types[i].name);
            fscanf(file, "%s %lf", Types[i].effects[j].defName, &Types[i].effects[j].multiplier);
            
        }

    }
    fclose(file)

    // Add "None" type
    strcpy(Types[18].name, "None");

    for (int j = 0; j < 19; j++) {
        strcpy(Types[18].effects[j].atkName, "None");
        strcpy(Types[18].effects[j].defName, Types[j].name);
        Types[18].effects[j].multiplier = 1.0;
    }
    
    
}