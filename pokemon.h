#ifndef POKEMON_H
#define POKEMON_H
#include "type.h"
#include "move.h"

typedef struct {
    char name[50];
    Type types[2];     
    int maxHP;
    int currentHP;
    int attack;
    int defense;
    int spAtk;
    int spDef;
    int speed;
    Move moves[4]; 
} Pokemon;

#endif