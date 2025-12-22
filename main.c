#include "type.h"
#include "move.h"
#include "pokemon.h"
#include "player.h"
#include "game.h" 
#include "utils.h" 

int main(void)
{
    Type Types[19];
    Move Moves[486];
    Pokemon Pokemons[1015];
    Player Player1;
    Player Player2;

    //arrayler adres olarak gider.
    initialize(Types, Moves, Pokemons, &Player1, &Player2);
    game(&Player1, &Player2);

    return 0;
}