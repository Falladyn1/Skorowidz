#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "index.h"

int main() {
    Indeks indeks;
    inicjalizujIndeks(&indeks);

    int opcja;
    char slowo[100];
    int strona;

    do {
        printf("\n==== MENU SKOROWIDZU ====\n");
        printf("1. Dodaj s³owo z numerem strony\n");
        printf("2. Wyœwietl indeks\n");
        printf("3. Zakoñcz\n");
        printf("Wybierz opcjê: ");
        if (scanf("%d", &opcja) != 1) {
            while (getchar() != '\n'); // czyszczenie bufora
            continue;
        }

        switch (opcja) {
        case 1:
            printf("Podaj s³owo: ");
            scanf("%s", slowo);
            printf("Podaj numer strony: ");
            scanf("%d", &strona);
            dodajSlowo(&indeks, slowo, strona);
            printf("Dodano!\n");
            break;
        case 2:
            printf("\n==== SKOROWIDZ ====\n");
            wypiszIndeks(&indeks);
            break;
        case 3:
            printf("Koniec programu.\n");
            break;
        default:
            printf("Niepoprawna opcja!\n");
        }
    } while (opcja != 3);

    zwolnijIndeks(&indeks);
    return 0;
}
