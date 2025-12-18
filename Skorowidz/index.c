#define _CRT_SECURE_NO_WARNINGS
#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicjalizujIndeks(Indeks* indeks) {
    indeks->pierwsze = NULL;
}

void dodajStrone(Slowo* s, int numer) {
    if (s->iloscStron == s->pojemnosc) {
        int nowaPojemnosc = (s->pojemnosc == 0) ? 4 : s->pojemnosc * 2;
        int* noweStrony = malloc(nowaPojemnosc * sizeof(int));

        if (noweStrony == NULL) exit(1);

        if (s->strony != NULL) {
            memcpy(noweStrony, s->strony, s->iloscStron * sizeof(int));
            free(s->strony);
        }

        s->strony = noweStrony;
        s->pojemnosc = nowaPojemnosc;
    }

    int i;
    for (i = 0; i < s->iloscStron; i++) {
        if (s->strony[i] == numer) return;
        if (s->strony[i] > numer) break;
    }

    for (int k = s->iloscStron; k > i; k--) {
        s->strony[k] = s->strony[k - 1];
    }

    s->strony[i] = numer;
    s->iloscStron++;
}

void dodajSlowo(Indeks* indeks, const char* tekst, int numer) {
    Slowo* aktualny = indeks->pierwsze;
    Slowo* poprzedni = NULL;

    while (aktualny != NULL) {
        int porownanie = strcmp(aktualny->tekst, tekst);

        if (porownanie == 0) {
            dodajStrone(aktualny, numer);
            return;
        }

        if (porownanie > 0) {
            break;
        }

        poprzedni = aktualny;
        aktualny = aktualny->nast;
    }

    Slowo* nowe = malloc(sizeof(Slowo));
    nowe->tekst = malloc(strlen(tekst) + 1);
    strcpy(nowe->tekst, tekst);
    nowe->strony = NULL;
    nowe->iloscStron = 0;
    nowe->pojemnosc = 0;
    dodajStrone(nowe, numer);

    if (poprzedni == NULL) {
        nowe->nast = indeks->pierwsze;
        indeks->pierwsze = nowe;
    }
    else {
        poprzedni->nast = nowe;
        nowe->nast = aktualny;
    }
}

void wypiszIndeks(const Indeks* indeks) {
    Slowo* s = indeks->pierwsze;
    if (!s) {
        printf("Indeks pusty.\n");
        return;
    }

    while (s) {
        printf("%s: ", s->tekst);
        for (int i = 0; i < s->iloscStron; i++) {
            printf("%d", s->strony[i]);
            if (i < s->iloscStron - 1) printf(", ");
        }
        printf("\n");
        s = s->nast;
    }
}

void zwolnijIndeks(Indeks* indeks) {
    Slowo* s = indeks->pierwsze;
    while (s) {
        Slowo* tmp = s;
        s = s->nast;
        free(tmp->tekst);
        free(tmp->strony);
        free(tmp);
    }
    indeks->pierwsze = NULL;
}
