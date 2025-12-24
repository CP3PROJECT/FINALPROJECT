#include "pokemon.h"
#include "player.h"
#include <stdio.h>
#include <string.h>

// PDF 2.2.8: Hasar hesaplama ve HP güncelleme fonksiyonu
void applyDamage(Player *Player1, Player *Player2, int choice1, int choice2, int moveIdx1, int moveIdx2) {
    Player *first, *second;
    int firstChoice, secondChoice, firstMove, secondMove;

    Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];
    Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

    // Hız kontrolü: Daha hızlı olan Pokémon önce saldırır.
    if (p1->speed >= p2->speed) {
        first = Player1; second = Player2;
        firstChoice = choice1; secondChoice = choice2;
        firstMove = moveIdx1; secondMove = moveIdx2;
    } else {
        first = Player2; second = Player1;
        firstChoice = choice2; secondChoice = choice1;
        firstMove = moveIdx2; secondMove = moveIdx1;
    }

    // İki saldırı aşaması (Önce hızlı olan, sonra yavaş olan)
    for (int i = 0; i < 2; i++) {
        Player *attacker = (i == 0) ? first : second;
        Player *defender = (i == 0) ? second : first;
        int currentChoice = (i == 0) ? firstChoice : secondChoice;
        int currentMoveIdx = (i == 0) ? firstMove : secondMove;

        Pokemon *atk = &attacker->Pokemons[attacker->currentIndex - 1];
        Pokemon *def = &defender->Pokemons[defender->currentIndex - 1];

        // Eğer oyuncu 'Change Pokemon' seçtiyse o tur saldıramaz.
        // Ayrıca defender zaten bayıldıysa veya attacker baygınsa saldırı gerçekleşmez.
        if (currentChoice == 2 || def->currentHP <= 0 || atk->currentHP <= 0) continue;

        Move *m = &atk->moves[currentMoveIdx];
        
        // Saldırı ve Savunma statlarının seçimi (Physical/Special ayrımı) [cite: 224, 225]
        double attackStat = (m->category == Physical_attack) ? atk->attack : atk->spAtk;
        double defenseStat = (m->category == Physical_attack) ? def->defense : def->spDef;

        // Tip Etkinliği (TypeEffect) hesaplama [cite: 226]
        double te1 = 1.0, te2 = 1.0;
        for (int j = 0; j < 19; j++) {
            // Hamle tipinin defender'ın birinci tipine etkisi
            if (strcmp(m->type.name, def->types[0].effects[j].atkName) == 0) {
                 te1 = m->type.effects[j].multiplier;
            }
            // Hamle tipinin defender'ın ikinci tipine etkisi (Eğer "None" değilse) 
            if (strcmp(def->types[1].name, "None") != 0) {
                if (strcmp(m->type.name, def->types[1].effects[j].atkName) == 0) {
                    te2 = m->type.effects[j].multiplier;
                }
            }
        }

        // STAB Kontrolü (Aynı Tip Saldırı Bonusu) [cite: 227]
        double stab = (strcmp(m->type.name, atk->types[0].name) == 0 || 
                       strcmp(m->type.name, atk->types[1].name) == 0) ? 1.5 : 1.0;

        // PDF'teki Final Hasar Formülü 
        double damage = m->power * (attackStat / defenseStat) * te1 * te2 * stab;
        
        def->currentHP -= (int)damage;
        if (def->currentHP < 0) def->currentHP = 0;

        printf("%s used %s! It dealt %d damage to %s.\n", atk->name, m->name, (int)damage, def->name);

        // Bayılma Kontrolü: Eğer Pokémon bayılırsa bir sonraki uygun olan seçilir[cite: 219, 229].
        if (def->currentHP <= 0) {
            printf("%s fainted!\n", def->name);
            for (int k = 0; k < 6; k++) {
                if (defender->Pokemons[k].currentHP > 0) {
                    defender->currentIndex = k + 1; // 1-tabanlı index [cite: 212]
                    printf("%s sent out %s!\n", defender->name, defender->Pokemons[k].name);
                    break;
                }
            }
            // Defender bayıldığı için bu tur saldırı sırası ondaysa saldıramaz.
            break; 
        }
    }
}

// PDF 2.2.7: Round fonksiyonu (Girişleri alır ve applyDamage'ı çağırır)
void roundFunction(Player *Player1, Player *Player2) {
    int choice1, choice2, moveIdx1 = -1, moveIdx2 = -1;

    // Player 1 Seçim [cite: 189-191]
    printf("\n--- %s's Turn (Active: %s) ---\n", Player1->name, Player1->Pokemons[Player1->currentIndex-1].name);
    printf("1- Attack\n2- Change Pokemon\nChoice: ");
    scanf("%d", &choice1);

    if (choice1 == 1) { // Attack [cite: 196]
        for (int i = 0; i < 4; i++) printf("%d- %s  ", i+1, Player1->Pokemons[Player1->currentIndex-1].moves[i].name);
        printf("\nSelect a move: ");
        scanf("%d", &moveIdx1); moveIdx1--; // 0-tabanlıya çevir [cite: 202]
    } else { // Change Pokemon [cite: 203]
        printf("Available Pokemons:\n");
        for (int i = 0; i < 6; i++) {
            if (Player1->Pokemons[i].currentHP > 0) printf("%d- %s (HP: %d)\n", i+1, Player1->Pokemons[i].name, Player1->Pokemons[i].currentHP);
        }
        printf("Select a Pokemon to switch: ");
        scanf("%d", &Player1->currentIndex); // currentIndex'i güncelle [cite: 212]
    }

    // Player 2 Seçim [cite: 192-194]
    printf("\n--- %s's Turn (Active: %s) ---\n", Player2->name, Player2->Pokemons[Player2->currentIndex-1].name);
    printf("1- Attack\n2- Change Pokemon\nChoice: ");
    scanf("%d", &choice2);

    if (choice2 == 1) {
        for (int i = 0; i < 4; i++) printf("%d- %s  ", i+1, Player2->Pokemons[Player2->currentIndex-1].moves[i].name);
        printf("\nSelect a move: ");
        scanf("%d", &moveIdx2); moveIdx2--;
    } else {
        printf("Available Pokemons:\n");
        for (int i = 0; i < 6; i++) {
            if (Player2->Pokemons[i].currentHP > 0) printf("%d- %s (HP: %d)\n", i+1, Player2->Pokemons[i].name, Player2->Pokemons[i].currentHP);
        }
        printf("Select a Pokemon to switch: ");
        scanf("%d", &Player2->currentIndex);
    }

    applyDamage(Player1, Player2, choice1, choice2, moveIdx1, moveIdx2);
}

// PDF 2.2.6: Game fonksiyonu (Döngü ve bitiş kontrolü)
void game(Player *Player1, Player *Player2) {
    while (1) {
        int p1_has_pokemon = 0, p2_has_pokemon = 0;

        // Oyunun bitip bitmediğini kontrol et 
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