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
        printf("\n1. Dodaj slowo\n2. Wyswietl\n0. Koniec\nWybierz: ");
        if (scanf("%d", &opcja) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (opcja) {
        case 1:
            printf("Podaj slowo: ");
            scanf("%s", slowo);
            printf("Podaj strone: ");
            scanf("%d", &strona);
            dodajSlowo(&indeks, slowo, strona);
            break;
        case 2:
            wypiszIndeks(&indeks);
            break;
        case 0:
            break;
        default:
            printf("Niepoprawna opcja\n");
        }
    } while (opcja != 0);

    zwolnijIndeks(&indeks);
    return 0;
}
