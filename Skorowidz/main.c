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
        printf("1. Dodaj slowo z numerem strony\n");
        printf("2. Wyswietl indeks\n");
        printf("0. Zakoncz\n");
        printf("Wybierz opcje: ");
        if (scanf("%d", &opcja) != 1) {
            while (getchar() != '\n'); 
            continue;
        }

        switch (opcja) {
        case 1:
            printf("Podaj slowo: ");
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
        case 0:
            printf("Koniec programu.\n");
            break;
        default:
            printf("Niepoprawna opcja!\n");
        }
    } while (opcja != 0);

    zwolnijIndeks(&indeks);
    return 0;
}
