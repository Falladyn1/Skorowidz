#ifndef INDEXER_H
#define INDEXER_H

typedef struct Slowo {
    char* tekst;
    int* strony;
    int iloscStron;
    int pojemnosc;
    struct Slowo* nast;
} Slowo;

typedef struct {
    Slowo* pierwsze;
} Indeks;

void inicjalizujIndeks(Indeks* indeks);
void dodajSlowo(Indeks* indeks, const char* tekst, int numer);
void wypiszIndeks(const Indeks* indeks);
void zwolnijIndeks(Indeks* indeks);

#endif
