#ifndef MOVE_H
#define MOVE_H
#include "type.h" 


typedef enum {
    Special_attack,
    Physical_attack
} Category;

typedef struct {
    char name[50];
    Type type;
    Category category;
    int power;
} Move;

void initializeMoves(Move Moves[], Type Types[]);

#endif