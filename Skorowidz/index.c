#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicjalizujIndeks(Indeks* indeks) {
    indeks->pierwsze = NULL;
}

void dodajStrone(Slowo* s, int numer) {
    if (s->iloscStron == s->pojemnosc) {
        s->pojemnosc = s->pojemnosc ? s->pojemnosc * 2 : 4;
        s->strony = realloc(s->strony, s->pojemnosc * sizeof(int));
    }
    s->strony[s->iloscStron++] = numer;
}

void dodajSlowo(Indeks* indeks, const char* tekst, int numer) {
    Slowo* s = indeks->pierwsze;
    while (s) {
        if (strcmp(s->tekst, tekst) == 0) {
            dodajStrone(s, numer);
            return;
        }
        s = s->nast;
    }

    s = malloc(sizeof(Slowo));
    s->tekst = _strdup(tekst);
    s->strony = NULL;
    s->iloscStron = 0;
    s->pojemnosc = 0;
    dodajStrone(s, numer);
    s->nast = indeks->pierwsze;
    indeks->pierwsze = s;
}

void drukujStrony(Slowo* s) {
    if (s->iloscStron == 0) return;

    int n = s->iloscStron;
    int* tab = malloc(n * sizeof(int));
    memcpy(tab, s->strony, n * sizeof(int));

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tab[i] > tab[j]) { int t = tab[i]; tab[i] = tab[j]; tab[j] = t; }

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

void wypiszIndeks(const Indeks* indeks) {
    int count = 0;
    Slowo* tmp = indeks->pierwsze;
    while (tmp) { count++; tmp = tmp->nast; }

    Slowo** tab = malloc(count * sizeof(Slowo*));
    tmp = indeks->pierwsze;
    for (int i = 0; i < count; i++) { tab[i] = tmp; tmp = tmp->nast; }

    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (strcmp(tab[i]->tekst, tab[j]->tekst) > 0) {
                Slowo* t = tab[i]; tab[i] = tab[j]; tab[j] = t;
            }

    for (int i = 0; i < count; i++) {
        printf("%s ", tab[i]->tekst);
        drukujStrony(tab[i]);
        printf("\n");
    }

    free(tab);
}

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
