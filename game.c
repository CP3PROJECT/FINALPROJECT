#include "pokemon.h"   // Pokemon struct'ı ve ilgili tanımlar
#include "player.h"    // Player struct'ı
#include <stdio.h>     // printf, scanf

// Bir turu (round) yöneten fonksiyon
void roundFunction(Player *Player1, Player *Player2, Type Types[19]) {

    // Oyuncuların ana seçimleri (1: Attack, 2: Change Pokemon)
    int choice1, choice2;

    // Seçilen move indexleri (henüz seçilmediği için -1)
    int moveIdx1 = -1, moveIdx2 = -1;

    // -------- PLAYER 1 ANA SEÇİM --------
    printf("Player 1, select your move:\n");
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");
    scanf("%d", &choice1);

    // -------- PLAYER 2 ANA SEÇİM --------
    printf("Player 2, select your move:\n");
    printf("1 - Attack\n");
    printf("2 - Change Pokemon\n");
    printf("Choice: ");
    scanf("%d", &choice2);

    // -------- PLAYER 1 DETAYLI SEÇİM --------
    if (choice1 == 1) {  
        // Player 1 saldırı seçtiyse

        // Aktif Pokemon'un adresi alınır
        // currentIndex 1'den başladığı için -1 yapılır
        Pokemon *p1 = &Player1->Pokemons[Player1->currentIndex - 1];

        // Pokemon'un 4 move'u listelenir
        for (int i = 0; i < 4; i++) {
            printf("%d - %-15s ", i + 1, p1->moves[i].name);

            // Her 2 move'da bir alt satıra geç
            if ((i + 1) % 2 == 0)
                printf("\n");
        }

        // Kullanıcıdan move seçimi alınır
        printf("Please select a move: ");
        scanf("%d", &moveIdx1);

        // 1–4 arası girilen değer 0–3 aralığına çevrilir
        moveIdx1--;

    } else {
        // Player 1 Pokemon değiştirmek isterse

        printf("Available Pokemons:\n");

        // Oyuncunun 6 Pokemon'u dolaşılır
        for (int i = 0; i < 6; i++) {

            // HP'si 0'dan büyük olanlar (ölü olmayanlar) listelenir
            if (Player1->Pokemons[i].currentHP > 0) {
                printf("%d - %s ", i + 1, Player1->Pokemons[i].name);
            }
        }

        // Yeni aktif Pokemon seçilir
        printf("\nPlease select a Pokemon to switch: ");
        scanf("%d", &Player1->currentIndex);
    }

    // -------- PLAYER 2 DETAYLI SEÇİM --------
    if (choice2 == 1) {
        // Player 2 saldırı seçtiyse

        // Player 2'nin aktif Pokemon'u
        Pokemon *p2 = &Player2->Pokemons[Player2->currentIndex - 1];

        // 4 move listelenir
        for (int i = 0; i < 4; i++) {
            printf("%d - %-15s ", i + 1, p2->moves[i].name);

            if ((i + 1) % 2 == 0)
                printf("\n");
        }

        // Move seçimi alınır
        printf("Please select a move: ");
        scanf("%d", &moveIdx2);

        // 0-tabanlı indexe çevirilir
        moveIdx2--;

    } else {
        // Player 2 Pokemon değiştirmek isterse

        printf("Available Pokemons:\n");

        for (int i = 0; i < 6; i++) {
            if (Player2->Pokemons[i].currentHP > 0) {
                printf("%d - %s ", i + 1, Player2->Pokemons[i].name);
            }
        }

        // Yeni aktif Pokemon seçilir
        printf("\nPlease select a Pokemon to switch: ");
        scanf("%d", &Player2->currentIndex);
    }

    // -------- HASAR HESAPLAMA --------
    // Tüm seçimler alındıktan sonra burada damage hesaplanacak
    // calculateDamage(Player1, Player2, choice1, choice2, moveIdx1, moveIdx2, Types);
}