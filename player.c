#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initialize(Type Types[], Move Moves[], Pokemon Pokemons[], Player* Player1, Player* Player2)
{
    initializeTypes(Types);
    initializeMoves(Moves, Types);
    initializePokemons(Pokemons, Moves, Types);

   // random pokemon assignment
    srand(time(NULL));

    //player names assignment
    strcpy(Player1->name, "Ayşegül");
    strcpy(Player2->name, "Safiye");

    // starting index assignment
    Player1->currentIndex = 1;
    Player2->currentIndex = 1;

   // Array to store the indices of the selected Pokémon
    int usedPokemon[1015] = {0};

    // random pokemons assignment to Player1
    for (int i = 0; i < 6; i++) {
        int index;

        do {
            index = rand() % 1015;
        } while (usedPokemon[index]);

        usedPokemon[index] = 1;
        Player1->Pokemons[i] = Pokemons[index];
    }

    // random pokemons assignment to Player2
    for (int i = 0; i < 6; i++) {
        int index;

        do {
            index = rand() % 1015;
        } while (usedPokemon[index]);

        usedPokemon[index] = 1;
        Player2->Pokemons[i] = Pokemons[index];
    }
}