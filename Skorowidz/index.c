#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicjalizacja indeksu
void inicjalizujIndeks(Indeks* indeks) {
    indeks->pierwsze = NULL;
}

// Dodanie strony do istniej¹cego s³owa
void dodajStrone(Slowo* s, int numer) {
    if (s->iloscStron == s->pojemnosc) {
        s->pojemnosc = s->pojemnosc ? s->pojemnosc * 2 : 4;
        s->strony = realloc(s->strony, s->pojemnosc * sizeof(int));
    }
    s->strony[s->iloscStron++] = numer;
}

// Dodanie s³owa lub dodanie strony, jeœli s³owo istnieje
void dodajSlowo(Indeks* indeks, const char* tekst, int numer) {
    Slowo* s = indeks->pierwsze;
    while (s) {
        if (strcmp(s->tekst, tekst) == 0) {
            dodajStrone(s, numer);
            return;
        }
        s = s->nast;
    }

    // Nowe s³owo
    s = malloc(sizeof(Slowo));
    s->tekst = _strdup(tekst); // Visual Studio
    s->strony = NULL;
    s->iloscStron = 0;
    s->pojemnosc = 0;
    dodajStrone(s, numer);
    s->nast = indeks->pierwsze;
    indeks->pierwsze = s;
}

// Drukowanie stron w formie zakresów
void drukujStrony(Slowo* s) {
    if (s->iloscStron == 0) return;

    int n = s->iloscStron;
    int* tab = malloc(n * sizeof(int));
    memcpy(tab, s->strony, n * sizeof(int));

    // Sortowanie
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tab[i] > tab[j]) { int t = tab[i]; tab[i] = tab[j]; tab[j] = t; }

    // Scalanie zakresów
    int start = tab[0], prev = tab[0];
    for (int i = 1; i < n; i++) {
        if (tab[i] == prev + 1) prev = tab[i];
        else {
            if (start == prev) printf("%d", start);
            else printf("%d-%d", start, prev);
            printf(", ");
            start = prev = tab[i];
        }
    }
    if (start == prev) printf("%d", start);
    else printf("%d-%d", start, prev);

    free(tab);
}

// Wypisanie ca³ego indeksu
void wypiszIndeks(const Indeks* indeks) {
    // Zliczamy iloœæ s³ów
    int count = 0;
    Slowo* tmp = indeks->pierwsze;
    while (tmp) { count++; tmp = tmp->nast; }

    // Tablica wskaŸników do s³ów
    Slowo** tab = malloc(count * sizeof(Slowo*));
    tmp = indeks->pierwsze;
    for (int i = 0; i < count; i++) { tab[i] = tmp; tmp = tmp->nast; }

    // Sortowanie alfabetyczne
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (strcmp(tab[i]->tekst, tab[j]->tekst) > 0) {
                Slowo* t = tab[i]; tab[i] = tab[j]; tab[j] = t;
            }

    // Drukowanie
    for (int i = 0; i < count; i++) {
        printf("%s ", tab[i]->tekst);
        drukujStrony(tab[i]);
        printf("\n");
    }

    free(tab);
}

// Zwolnienie pamiêci
void zwolnijIndeks(Indeks* indeks) {
    Slowo* s = indeks->pierwsze;
    while (s) {
        Slowo* tmpS = s;
        s = s->nast;
        free(tmpS->tekst);
        free(tmpS->strony);
        free(tmpS);
    }
}
