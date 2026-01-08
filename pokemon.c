#include "pokemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializePokemons(Pokemon Pokemons[], Move Moves[], Type Types[]) {
    // Open file
    FILE *file = fopen("pokemon.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open pokemon.txt!\n");
        return;
    }

    char type1Name[50], type2Name[50];

    for (int i = 0; i < 1015; i++) {
        // Read the data
        fscanf(file, "%s %s %s %d %d %d %d %d %d", 
               Pokemons[i].name, type1Name, type2Name, 
               &Pokemons[i].maxHP, &Pokemons[i].attack, &Pokemons[i].defense, 
               &Pokemons[i].spAtk, &Pokemons[i].spDef, &Pokemons[i].speed);

        Pokemons[i].currentHP = Pokemons[i].maxHP;

        //  Matching types
        for (int j = 0; j < 18; j++) {
            // First type match
            if (strcmp(type1Name, Types[j].name) == 0) {
                Pokemons[i].types[0] = Types[j];
            }

            // Second type check: "-" = none
            if (strcmp(type2Name, "-") == 0) {
                Pokemons[i].types[1] = Types[18];
            } else {
                for (int j = 0; j < 18; j++) {
                    if (strcmp(type2Name, Types[j].name) == 0) {
                    Pokemons[i].types[1] = Types[j];
                    break;
                    }
                }
            }
        }

        // Randomly Select 4 Unique Moves
        int count = 0;
        while (count < 4) {
            int randomIdx = rand() % 486; 
            int isDuplicate = 0;

            // Unique check
            for (int k = 0; k < count; k++) { 
                if (strcmp(Pokemons[i].moves[k].name, Moves[randomIdx].name) == 0) {
                    isDuplicate = 1;
                    break;
                }
            }

            // Add the movement if it's new.
            if (!isDuplicate) {
                Pokemons[i].moves[count] = Moves[randomIdx];
                count++;
            }
        }
    }
    fclose(file);
}