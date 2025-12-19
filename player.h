#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"

typedef struct {
    char name[50];
    Pokemon Pokemons[6];
    int currentIndex;     
} Player;

#endif