#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"

typedef struct {
    char name[50];
    Pokemon Pokemons[6];
    int currentIndex;     
} Player;

void initialize(Type Types[], Move Moves[], Pokemon Pokemons[], Player* Player1, Player* Player2);

#endif