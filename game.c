#include "pokemon.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

// Damage calculation function
void applyDamage(Player *Player1, Player *Player2, int choice1, int choice2, int moveIdx1, int moveIdx2) {
    Player *first, *second;
    int firstChoice, secondChoice, firstMove, secondMove;

    //active Pokemons for player1 and player2
    Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];
    Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

    // speed control 
    if (p1->speed >= p2->speed) {
        first = Player1;
        second = Player2;
        firstChoice = choice1; 
        secondChoice = choice2;
        firstMove = moveIdx1;
        secondMove = moveIdx2;
    } else {
        first = Player2;
        second = Player1;
        firstChoice = choice2;
        secondChoice = choice1;
        firstMove = moveIdx2;
        secondMove = moveIdx1;
    }

    // Apply actions in order
    for (int i = 0; i < 2; i++) {
        Player *attacker = (i == 0) ? first : second;
        Player *defender = (i == 0) ? second : first;
        int currentChoice = (i == 0) ? firstChoice : secondChoice;
        int currentMoveIdx = (i == 0) ? firstMove : secondMove;

        Pokemon *atk = &attacker->Pokemons[attacker->currentIndex - 1];
        Pokemon *def = &defender->Pokemons[defender->currentIndex - 1];

        //Skip attack if Pokémon is switched or fainted
        if (currentChoice == 2 || def->currentHP <= 0 || atk->currentHP <= 0) continue;

        Move *m = &atk->moves[currentMoveIdx];
        
        // select appropriate attack and defense stats.
        double attackStat = (m->category == Physical_attack) ? atk->attack : atk->spAtk;
        double defenseStat = (m->category == Physical_attack) ? def->defense : def->spDef;

        // Type Effect calculation.
        double te1 = 1.0, te2 = 1.0;
        for (int j = 0; j < 19; j++) {
            //Effect of move type on defender's first type
            if (strcmp(m->type.name, def->types[0].effects[j].atkName) == 0) {
                 te1 = m->type.effects[j].multiplier;
            }
            
            if (strcmp(def->types[1].name, "None") != 0) {
                if (strcmp(m->type.name, def->types[1].effects[j].atkName) == 0) {
                    te2 = m->type.effects[j].multiplier;
                }
            }
        }

        // STAB Control
        double stab = (strcmp(m->type.name, atk->types[0].name) == 0 || 
                       strcmp(m->type.name, atk->types[1].name) == 0) ? 1.5 : 1.0;

        // Final Damage Calculation
        double damage = m->power * (attackStat / defenseStat) * te1 * te2 * stab;
        
        def->currentHP -= (int)damage;
        if (def->currentHP < 0) def->currentHP = 0;

        printf("%s used %s! It dealt %d damage to %s.\n", atk->name, m->name, (int)damage, def->name);

        //Fainting control
        if (def->currentHP <= 0) {
            printf("%s fainted!\n", def->name);
            for (int k = 0; k < 6; k++) {
                if (defender->Pokemons[k].currentHP > 0) {
                    defender->currentIndex = k + 1; 
                    printf("%s sent out %s!\n", defender->name, defender->Pokemons[k].name);
                    break;
                }
            }
            
            break; 
        }
    }
}



void roundFunction(Player *Player1, Player *Player2) {
    int choice1, choice2, moveIdx1 = -1, moveIdx2 = -1;

    // Player 1 decision (Attack or Change)
    do {
        Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1]; 
        printf("\n--- %s's Decision (Active: %s - HP: %d) ---\n", 
               Player1->name, p1->name, p1->currentHP);
        printf("1- Attack\n2- Change Pokemon\nChoice: ");
        
        if (scanf("%d", &choice1) != 1) {
            printf("Error: Invalid input! Please enter 1 or 2!\n");
            while(getchar() != '\n')
                continue; 
            choice1 = 0; 
            continue;
        }
        if (choice1 != 1 && choice1 != 2) {
            printf("Invalid choice! Please choose 1 or 2!\n");
        }
    } while(choice1 != 1 && choice1 != 2);

    // Player 2 decision (Attack or Change)
    do {
        Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];
        printf("\n--- %s's Decision (Active: %s - HP: %d) ---\n", 
               Player2->name, p2->name, p2->currentHP);
        printf("1- Attack\n2- Change Pokemon\nChoice: ");
        
        if (scanf("%d", &choice2) != 1) {
            printf("Error: Invalid input! Please try again.\n");
            while(getchar() != '\n')
                continue; 
            choice2 = 0;
            continue;
        }
        if (choice2 != 1 && choice2 != 2) {
            printf("Invalid choice! Please choose 1 or 2!\n");
        }
    } while (choice2 != 1 && choice2 != 2);

    //Player 1 move or pokemon selection
    Pokemon *p1_detail = &Player1->Pokemons[Player1->currentIndex - 1];
    if (choice1 == 1) { // SALDIRI DETAYI
        while (1) {
            printf("\n%s, select your move: \n", Player1->name);
            for (int i = 0; i < 4; i++) 
                printf("%d- %s  ", i+1, p1_detail->moves[i].name);
            
            printf("\nSelect a move (1-4): ");
            if (scanf("%d", &moveIdx1) != 1) {
                while(getchar() != '\n')
                    continue;
                printf("Error: Please enter a number!\n");
                continue;
            }
            if (moveIdx1 >= 1 && moveIdx1 <= 4) {
                moveIdx1--; 
                break;
            } else {
                printf("[WARNING] Invalid selection! Please choose a move between 1 and 4.\n");
            }
        }
    } else {  //change pokemon
        int switchIdx;
        while (1) {
            printf("\n%s, available Pokemons:\n", Player1->name);
            for (int i = 0; i < 6; i++) {
                if (Player1->Pokemons[i].currentHP > 0) {
                    printf("%d- %s (HP: %d)\n", i+1, Player1->Pokemons[i].name, Player1->Pokemons[i].currentHP);
                }
            }
            printf("Select a Pokemon to switch: ");
            if (scanf("%d", &switchIdx) != 1) {
                while(getchar() != '\n')
                    continue;
                printf("\nError: Please enter a number!\n\n");
                continue;
            }
            if (switchIdx >= 1 && switchIdx <= 6 && Player1->Pokemons[switchIdx-1].currentHP > 0) {
                Player1->currentIndex = switchIdx;
                break;
            } else {
                printf("\n[WARNING] Invalid selection! Please choose an active Pokemon from the list.\n\n");
            }
        }
    }

    //Player 2 move or pokemon selection
    Pokemon *p2_detail = &Player2->Pokemons[Player2->currentIndex - 1];
    if (choice2 == 1) { // choose attack 
        while (1) {
            printf("\n%s, select your move: \n", Player2->name);
            for (int i = 0; i < 4; i++) 
                printf("%d- %s  ", i+1, p2_detail->moves[i].name);
            
            printf("\nSelect a move (1-4): ");
            if (scanf("%d", &moveIdx2) != 1) {
                while(getchar() != '\n')
                    continue;
                printf("Error: Please enter a number!\n");
                continue;
            }
            if (moveIdx2 >= 1 && moveIdx2 <= 4) {
                moveIdx2--;
                break;
            } else {
                printf("[WARNING] Invalid selection! Please choose a move between 1 and 4.\n");
            }
        }
    } else { // change pokemon
        int switchIdx;
        while (1) {
            printf("\n%s, available Pokemons:\n", Player2->name);
            for (int i = 0; i < 6; i++) {
                if (Player2->Pokemons[i].currentHP > 0) {
                    printf("%d- %s (HP: %d)\n", i+1, Player2->Pokemons[i].name, Player2->Pokemons[i].currentHP);
                }
            }
            printf("Select a Pokemon to switch: ");
            if (scanf("%d", &switchIdx) != 1) {
                while(getchar() != '\n')
                    continue;
                printf("\nError: Please enter a number!\n\n");
                continue;
            }
            if (switchIdx >= 1 && switchIdx <= 6 && Player2->Pokemons[switchIdx-1].currentHP > 0) {
                Player2->currentIndex = switchIdx;
                break; 
            } else {
                printf("\n[WARNING] Invalid selection! Please choose an active Pokemon from the list.\n\n");
            }
        }
    }

    // call applyDamage function
    applyDamage(Player1, Player2, choice1, choice2, moveIdx1, moveIdx2);
}

// game function
void game(Player *Player1, Player *Player2) {
    while (1) {
        int p1_has_pokemon = 0, p2_has_pokemon = 0;

        // Check if any player has no remaining Pokemons
        for (int i = 0; i < 6; i++) {
            if (Player1->Pokemons[i].currentHP > 0) p1_has_pokemon = 1;
            if (Player2->Pokemons[i].currentHP > 0) p2_has_pokemon = 1;
        }

        if (!p1_has_pokemon) {
            printf("\n*** %s has no more Pokemons! %s wins the game! ***\n", Player1->name, Player2->name);
            break;
        }
        if (!p2_has_pokemon) {
            printf("\n*** %s has no more Pokemons! %s wins the game! ***\n", Player2->name, Player1->name);
            break;
        }

        roundFunction(Player1, Player2);
    }
}