#include "type.h"
#include "move.h"
#include "pokemon.h"
#include "player.h"
#include "game.h" 
#include "stdio.h"

    Type Types[19];
    Move Moves[486];
    Pokemon Pokemons[1015];
    Player Player1;
    Player Player2;

// gcc -Wall -Werror -Wextra *.c -o project 

int main(void)
{
    printf("Program basladi...\n");
    
    printf("Initialize ediliyor...\n");
    //arrayler adres olarak gider.
    initialize(Types, Moves, Pokemons, &Player1, &Player2);
    
    printf("Oyun basliyor...\n");
    game(&Player1, &Player2);

    return 0;
}