#include "pokemon.h"#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"

void initializePokemons(Pokemon Pokemons[], Move Moves[], Type Types[]) {
    // 1. Dosyayı açıyoruz
    FILE *file = fopen("pokemon.txt", "r");
    if (file == NULL) {
        printf("Pokemon dosyasi bulunamadi!\n");
        return;
    }

    char type1Name[50], type2Name[50];

    for (int i = 0; i < 1015; i++) {
        // 2. Verileri okuyoruz: İsim, Tip1, Tip2, HP, Atk, Def, SpAtk, SpDef, Speed
        fscanf(file, "%s %s %s %d %d %d %d %d %d", 
               Pokemons[i].name, type1Name, type2Name, 
               &Pokemons[i].maxHP, &Pokemons[i].attack, &Pokemons[i].defense, 
               &Pokemons[i].spAtk, &Pokemons[i].spDef, &Pokemons[i].speed);

        // 3. Mevcut canı maksimum cana eşitle
        Pokemons[i].currentHP = Pokemons[i].maxHP;

        // 4. Tipleri Eşleştirme (Type1 ve Type2)
        for (int j = 0; j < 18; j++) {
            // Birinci tip eşleşmesi
            if (strcmp(type1Name, Types[j].name) == 0) {
                Pokemons[i].types[0] = Types[j];
            }

            // İkinci tip kontrolü: Eğer "-" ise "None" yap
            if (strcmp(type2Name, "-") == 0) {
                // Döküman kuralı: "-" ise Types[18] (None) ata
                Pokemons[i].types[1] = Types[18];
            } else {
                // Değilse gerçek tipi ara
                for (int j = 0; j < 18; j++) {
                    if (strcmp(type2Name, Types[j].name) == 0) {
                    Pokemons[i].types[1] = Types[j];
                    break;
                    }
                }
            }
        }

        // 5. Rastgele 4 Adet Benzersiz Hareket (Move) Seçme
        int count = 0;
        while (count < 4) {
            int randomIdx = rand() % 486; // 0 ile 485 arası rastgele sayı
            int isDuplicate = 0;

            // Seçilen hareket daha önce eklenmiş mi kontrol et (Unique kontrolü)
            for (int k = 0; k < count; k++) { 
                if (strcmp(Pokemons[i].moves[k].name, Moves[randomIdx].name) == 0) {
                    isDuplicate = 1;
                    break;
                }
            }

            // Eğer hareket yeni ise ekle
            if (!isDuplicate) {
                Pokemons[i].moves[count] = Moves[randomIdx];
                count++;
            }
        }
    }
    fclose(file);
}