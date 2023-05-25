#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct Proizvod proizvodi[MAX_PROIZVODA];
int broj_proizvoda = 0;

void ispis_izbornika_vlasnik() {
    printf("\nTrgovinu pregledavate kao Vlasnik:\n");
    printf("-----------------------------\n");
    printf("1. Pregled svih proizvoda\n");
    printf("-----------------------------\n");
    printf("2. Dodavanje novog proizvoda\n");
    printf("-----------------------------\n");
    printf("3. Izmjena stanja proizvoda\n");
    printf("-----------------------------\n");
    printf("4. Nova narudzba\n");
    printf("-----------------------------\n");
    printf("5. Sortiranje proizvoda\n");
    printf("-----------------------------\n");
    printf("6. Ucitaj podatke iz datoteke\n");
    printf("-----------------------------\n");
    printf("7. Povratak na pocetni izbornik\n");
    printf("-----------------------------\n");
    printf("0. Izlaz\n");
    printf("-----------------------------\n");
    printf("Odabir: ");
}

void ispis_izbornika_kupac() {
    printf("\nTrgovinu pregledavate kao Kupac:\n");
    printf("-----------------------------\n");
    printf("1. Nova narudzba\n");
    printf("-----------------------------\n");
    printf("2. Pregled svih proizvoda\n");
    printf("-----------------------------\n");
    printf("3. Povratak na pocetni izbornik\n");
    printf("-----------------------------\n");
    printf("0. Izlaz\n");
    printf("-----------------------------\n");
    printf("Odabir: ");
}

void pregled_proizvoda() {
    printf("\nPopis proizvoda:\n");
    printf("SKU     \tNaziv       \tStanje  \n");

    FILE* datoteka = fopen("popis_proizvoda.txt", "r");
    if (datoteka == NULL) {
        printf("Nije moguće otvoriti datoteku.");
        return;
    }

    struct Proizvod ucitani_proizvod;
    while (fscanf(datoteka, "SKU: %d", &ucitani_proizvod.sku) == 1) {
        fscanf(datoteka, "\nNaziv: %[^\n]", ucitani_proizvod.naziv);
        fscanf(datoteka, "\nStanje: %d", &ucitani_proizvod.stanje);
        fscanf(datoteka, "\n");

        printf("%d\t%s\t%d\n", ucitani_proizvod.sku, ucitani_proizvod.naziv, ucitani_proizvod.stanje);
    }

    fclose(datoteka);
}

struct Proizvod proizvodi[MAX_PROIZVODA];

void dodaj_proizvod() {
    if (broj_proizvoda >= MAX_PROIZVODA) {
        printf("Dosegnut maksimalni broj proizvoda.\n");
        return;
    }

    struct Proizvod novi_proizvod;
    printf("\nDodavanje novog proizvoda:\n");
    printf("SKU: ");
    scanf("%d", &novi_proizvod.sku);
    printf("Naziv: ");
    scanf(" %[^\n]s", novi_proizvod.naziv);
    printf("Stanje: ");
    scanf("%d", &novi_proizvod.stanje);

    proizvodi[broj_proizvoda] = novi_proizvod;
    broj_proizvoda++;

    FILE* datoteka = fopen("popis_proizvoda.txt", "a");
    if (datoteka == NULL) {
        printf("Nije moguće otvoriti datoteku.");
        return;
    }

    fprintf(datoteka, "SKU: %d\n", novi_proizvod.sku);
    fprintf(datoteka, "Naziv: %s\n", novi_proizvod.naziv);
    fprintf(datoteka, "Stanje: %d\n\n", novi_proizvod.stanje);

    fclose(datoteka);
    printf("Proizvod uspješno dodan.\n");
}


void ucitaj_iz_datoteke() {
        FILE* datoteka = fopen("popis_proizvoda.txt", "r");
        if (datoteka == NULL) {
            printf("Nije moguće otvoriti datoteku.\n");
            return;
        }

        broj_proizvoda = 0;

        while (fscanf(datoteka, "SKU: %d\n", &proizvodi[broj_proizvoda].sku) == 1) {
            fscanf(datoteka, "Naziv: %[^\n]\n", proizvodi[broj_proizvoda].naziv);
            fscanf(datoteka, "Stanje: %d\n\n", &proizvodi[broj_proizvoda].stanje);
            broj_proizvoda++;
        }

        fclose(datoteka);

        printf("Podaci uspjesno ucitani iz datoteke.\n");
    }
void izmjena_stanja() {
    ucitaj_iz_datoteke();
    int sku;
    int novo_stanje;
    printf("\nIzmjena stanja proizvoda:\n");
    printf("Unesite SKU proizvoda: ");
    scanf("%d", &sku);
    printf("Unesite novo stanje: ");
    scanf("%d", &novo_stanje);

    int pronaden = 0;
    for (int i = 0; i < broj_proizvoda; i++) {
        if (proizvodi[i].sku == sku) {
            proizvodi[i].stanje = novo_stanje;
            pronaden = 1;
            break;
        }
    }

    if (pronaden) {
        FILE* datoteka = fopen("popis_proizvoda.txt", "w");
        if (datoteka == NULL) {
            printf("Nije moguće otvoriti datoteku.");
            return;
        }

        for (int i = 0; i < broj_proizvoda; i++) {
            fprintf(datoteka, "SKU: %d\n", proizvodi[i].sku);
            fprintf(datoteka, "Naziv: %s\n", proizvodi[i].naziv);
            fprintf(datoteka, "Stanje: %d\n\n", proizvodi[i].stanje);
            printf("SKU: %d\tNaziv: %s\tStanje: %d\n", proizvodi[i].sku, proizvodi[i].naziv, proizvodi[i].stanje);
        }

        fclose(datoteka);

        printf("Stanje proizvoda uspješno izmijenjeno.\n");
    }
    else {
        printf("Proizvod sa SKU-om %d nije pronađen.\n", sku);
    }
}

void nova_narudzba() {
    ucitaj_iz_datoteke();
    struct Narudzba nova_narudzba;
    printf("\nNova narudzba:\n");
    printf("SKU proizvoda: ");
    scanf("%d", &nova_narudzba.sku);
    printf("Naziv proizvoda: ");
    scanf(" %[^\n]s", nova_narudzba.naziv);
    printf("Kolicina: ");
    scanf("%d", &nova_narudzba.kolicina);

    int pronaden = 0;
    for (int i = 0; i < broj_proizvoda; i++) {
        if (proizvodi[i].sku == nova_narudzba.sku) {
            if (proizvodi[i].stanje >= nova_narudzba.kolicina) {
                proizvodi[i].stanje -= nova_narudzba.kolicina;
                pronaden = 1;
                break;
            }
            else {
                printf("Nedovoljna kolicina proizvoda na stanju.\n");
                return;
            }
        }
    }

    if (pronaden) {
        FILE* datoteka = fopen("popis_proizvoda.txt", "w");
        if (datoteka == NULL) {
            printf("Nije moguće otvoriti datoteku.");
            return;
        }

        for (int i = 0; i < broj_proizvoda; i++) {
            fprintf(datoteka, "SKU: %d\n", proizvodi[i].sku);
            fprintf(datoteka, "Naziv: %s\n", proizvodi[i].naziv);
            fprintf(datoteka, "Stanje: %d\n\n", proizvodi[i].stanje);
        }

        fclose(datoteka);
        printf("--------------------------------CESTITAMO--------------------------\n");
        printf("Narudzba uspjesno kreirana. Hvala vam sto koristite Kadar trgovinu.\n");
        printf("-------------------------------------------------------------------\n");
    }
    else {
        printf("Proizvod sa SKU-om %d nije pronaden. Molimo pokusajte ponovno\n", nova_narudzba.sku);
    }
}

void sortiraj_proizvode() {
    int odabir;
    printf("\nSortiranje proizvoda:\n");
    printf("-----------------------------\n");
    printf("1. Sortiraj po imenu\n");
    printf("2. Sortiraj po SKU\n");
    printf("-----------------------------\n");
    printf("Odabir: ");
    scanf("%d", &odabir);

    switch (odabir) {
    case 1:
        usporedi_po_imenu();
        break;
    case 2:
        usporedi_po_sku();
        break;
    default:
        printf("Neispravan odabir.\n");
        return;
    }

    printf("Proizvodi uspjesno sortirani.\n");
}

void usporedi_po_imenu(const void* a, const void* b) {
    const struct Proizvod* proizvod_a = (const struct Proizvod*)a;
    const struct Proizvod* proizvod_b = (const struct Proizvod*)b;

    return strcmp(proizvod_a->naziv, proizvod_b->naziv);
}

void usporedi_po_sku(const void* a, const void* b) {
    const struct Proizvod* proizvod_a = (const struct Proizvod*)a;
    const struct Proizvod* proizvod_b = (const struct Proizvod*)b;

    return proizvod_a->sku - proizvod_b->sku;
}
