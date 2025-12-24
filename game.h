#ifndef GAME_H
#define GAME_H

#include "player.h" // Player, Pokemon, Move ve Type'ı zincirleme getirir

void game(Player *p1, Player *p2);
void roundFunction(Player *p1, Player *p2);
void applyDamage(Player *p1, Player *p2, int choice1, int choice2, int moveIdx1, int moveIdx2);

#endif