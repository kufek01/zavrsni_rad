#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static broj_proizvoda = 0;
static int i;
static int j;
static int br = 0;
//********************************************IZBORNICI***************************************************//
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
    printf("6. Brisanje proizvoda\n");
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
//********************************************PREGLED PROZIVODA***************************************************//
void* pregled_proizvoda() {
    printf("\nPopis proizvoda:\n");
    printf("SKU   \tNaziv\t\t\t\tCijena\t\tKategorija\tStanje\n");
    printf("---------------------------------------------------------------------------------------\n");

    FILE* datoteka = fopen("proizvodi.bin", "rb");
    if (datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku.");
        return NULL;
    }

    int broj_proizvoda;
    fread(&broj_proizvoda, sizeof(int), 1, datoteka);

    PROIZVOD* proizvodi = (PROIZVOD*)malloc(broj_proizvoda * sizeof(PROIZVOD));
    if (proizvodi == NULL) {
        printf("Nedovoljno memorije.");
        fclose(datoteka);
        return NULL;
    }

    int i;
    for (i = 0; i < broj_proizvoda; i++) {
        if (fread(&proizvodi[i], sizeof(PROIZVOD), 1, datoteka) != 1) {
            printf("Greška prilikom èitanja proizvoda iz datoteke.");
            fclose(datoteka);
            free(proizvodi);
            return NULL;
        }

        printf("%-6d\t%-24s\t%-12d\t%-16s\t%d\n",
            proizvodi[i].sku,
            proizvodi[i].ime,
            proizvodi[i].cijena,
            proizvodi[i].kategorija,
            proizvodi[i].kolicina);
    }

    printf("---------------------------------------------------------------------------------------\n");

    fclose(datoteka);
    return proizvodi;
}

//********************************************DODAVANJE PROZIVODA***************************************************//
void dodaj_proizvod() {
    FILE* datoteka = fopen("proizvodi.bin", "r+b");
    if (datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku.");
        return;
    }

    int broj_proizvoda = 0;
    fread(&broj_proizvoda, sizeof(int), 1, datoteka);
    broj_proizvoda++;

    PROIZVOD proizvod;
    proizvod.sku = broj_proizvoda;
    getchar();
    printf("\nUnesite kategoriju: ");
    fgets(proizvod.kategorija, sizeof(proizvod.kategorija), stdin);
    proizvod.kategorija[strcspn(proizvod.kategorija, "\n")] = '\0';
    printf("\nUnesite ime proizvoda: ");
    fgets(proizvod.ime, sizeof(proizvod.ime), stdin);
    proizvod.ime[strcspn(proizvod.ime, "\n")] = '\0';
    printf("\nUnesite cijenu: ");
    scanf("%d", &proizvod.cijena);
    printf("\nUnesite kolicinu: ");
    scanf("%d", &proizvod.kolicina);

    fseek(datoteka, 0, SEEK_SET);
    fwrite(&broj_proizvoda, sizeof(int), 1, datoteka);
    fseek(datoteka, 0, SEEK_END);
    fwrite(&proizvod, sizeof(PROIZVOD), 1, datoteka);

    fclose(datoteka);
}

//********************************************IZMJENA STANJA***************************************************//
void izmjena_stanja() {
    pregled_proizvoda();
    FILE* fp = fopen("proizvodi.bin", "rb+");
    if (fp == NULL) {
        perror("Otvaranje datoteke");
        return;
    }

    fread(&broj_proizvoda, sizeof(int), 1, fp);
    if (broj_proizvoda == 0) {
        printf("Nema dostupnih proizvoda.\n");
        fclose(fp);
        return;
    }

    PROIZVOD* polje = (PROIZVOD*)calloc(broj_proizvoda, sizeof(PROIZVOD));
    if (polje == NULL) {
        perror("Zauzimanje memorije");
        fclose(fp);
        return;
    }

    fread(polje, sizeof(PROIZVOD), broj_proizvoda, fp);

    int sku;
    printf("Unesite SKU proizvoda za izmjenu stanja: ");
    scanf("%d", &sku);

    int i;
    for (i = 0; i < broj_proizvoda; i++) {
        if (polje[i].sku == sku) {
            int nova_kolicina;
            printf("Trenutna kolicina: %d\n", polje[i].kolicina);
            printf("Unesite novu kolicinu: ");
            scanf("%d", &nova_kolicina);

            polje[i].kolicina = nova_kolicina;
            fseek(fp, sizeof(int) + i * sizeof(PROIZVOD), SEEK_SET);
            fwrite(&polje[i], sizeof(PROIZVOD), 1, fp);
            printf("Stanje proizvoda je uspjesno izmijenjeno.\n");
            break;
        }
    }

    if (i == broj_proizvoda) {
        printf("Proizvod s unesenim SKU brojem nije pronaden.\n");
    }

    free(polje);
    fclose(fp);
}
//********************************************NOVA NARUDZBA***************************************************//
void nova_narudzba() {
    FILE* fp = fopen("proizvodi.bin", "rb+");
    if (fp == NULL) {
        perror("Otvaranje datoteke");
        return;
    }

    fread(&broj_proizvoda, sizeof(int), 1, fp);
    if (broj_proizvoda == 0) {
        printf("Nema dostupnih proizvoda za narudzbu.\n");
        fclose(fp);
        return;
    }

    PROIZVOD* polje = (PROIZVOD*)calloc(broj_proizvoda, sizeof(PROIZVOD));
    if (polje == NULL) {
        perror("Zauzimanje memorije");
        fclose(fp);
        return;
    }

    fread(polje, sizeof(PROIZVOD), broj_proizvoda, fp);

    int sku;
    printf("Unesite SKU proizvoda za narudzbu: ");
    scanf("%d", &sku);

    int i;
    for (i = 0; i < broj_proizvoda; i++) {
        if (polje[i].sku == sku) {
            int kolicina;
            printf("Unesite kolicinu za narudzbu: ");
            scanf("%d", &kolicina);

            if (polje[i].kolicina < kolicina) {
                printf("Nema dovoljno proizvoda na stanju.\n");
                break;
            }

            polje[i].kolicina -= kolicina;
            fseek(fp, sizeof(int) + i * sizeof(PROIZVOD), SEEK_SET);
            fwrite(&polje[i], sizeof(PROIZVOD), 1, fp);
            printf("Narudzba je uspjesno izvrsena.\n");
            break;
        }
    }

    if (i == broj_proizvoda) {
        printf("Proizvod s unesenim SKU brojem nije pronaden.\n");
    }

    free(polje);
    fclose(fp);
}
//********************************************SORTIRANJE PROIZVODA***************************************************//
int sortiraj_proizvode() {
    int uvijet = 0;
    PROIZVOD* proizvodi = (PROIZVOD*)pregled_proizvoda();
    if (proizvodi == NULL) {
        printf("Nema dostupnih proizvoda.\n");
        return 0;
    }
    
    FILE* fp = fopen("proizvodi.bin", "rb");
    if (fp == NULL) {
        perror("Otvaranje proizvodi.bin");
        exit(1);
    }
    fread(&broj_proizvoda, sizeof(int), 1, fp);
    fclose(fp);


    printf("Sortiranje.\n\n");
    printf("Opcija 1: Cijena od najjeftinijeg do najskupljeg\n");
    printf("Opcija 2: Cijena od najskupljeg do najjeftinijeg\n");
    printf("Opcija 3: Povratak\n");
    printf("ODABIR: ");
    scanf("%d", &uvijet);
    fflush(stdin);
    system("cls");

    switch (uvijet) {
    case 1:
        najjeftinije_do_najskuplje(proizvodi, broj_proizvoda);
        break;
    case 2:
        najskuplje_do_najjeftinije(proizvodi, broj_proizvoda);
        break;
    case 3:
        free(proizvodi);  // Oslobodi memoriju
        return 89;
    default:
        printf("\nPogresan unos!\n");
        break;
    }

    free(proizvodi);  // Oslobodi memoriju

    return uvijet;
}

void najjeftinije_do_najskuplje(PROIZVOD* proizvodi, int broj_proizvoda) {
    // Sortiranje proizvoda prema cijeni - najjeftiniji do najskuplji
    int i, j;
    PROIZVOD temp;
    for (i = 0; i < broj_proizvoda - 1; i++) {
        for (j = 0; j < broj_proizvoda - i - 1; j++) {
            if (proizvodi[j].cijena > proizvodi[j + 1].cijena) {
                temp = proizvodi[j];
                proizvodi[j] = proizvodi[j + 1];
                proizvodi[j + 1] = temp;
            }
        }
    }

    printf("\nProizvodi - najjeftiniji do najskuplji:\n");
    printf("SKU   \tNaziv\t\t\t\tCijena\t\tKategorija\tStanje\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < broj_proizvoda; i++) {
        printf("%-6d\t%-24s\t%-12d\t%-16s\t%d\n",
            proizvodi[i].sku,
            proizvodi[i].ime,
            proizvodi[i].cijena,
            proizvodi[i].kategorija,
            proizvodi[i].kolicina);
    }

    printf("---------------------------------------------------------------\n");
}

void najskuplje_do_najjeftinije(PROIZVOD* proizvodi, int broj_proizvoda) {
    // Sortiranje proizvoda prema cijeni - najskuplji do najjeftiniji
    int i, j;
    PROIZVOD temp;
    for (i = 0; i < broj_proizvoda - 1; i++) {
        for (j = 0; j < broj_proizvoda - i - 1; j++) {
            if (proizvodi[j].cijena < proizvodi[j + 1].cijena) {
                temp = proizvodi[j];
                proizvodi[j] = proizvodi[j + 1];
                proizvodi[j + 1] = temp;
            }
        }
    }

    printf("\nProizvodi - najskuplji do najjeftiniji:\n");
    printf("SKU   \tNaziv\t\t\t\tCijena\t\tKategorija\tStanje\n");
    printf("---------------------------------------------------------------\n");

    for (i = 0; i < broj_proizvoda; i++) {
        printf("%-6d\t%-24s\t%-12d\t%-16s\t%d\n",
            proizvodi[i].sku,
            proizvodi[i].ime,
            proizvodi[i].cijena,
            proizvodi[i].kategorija,
            proizvodi[i].kolicina);
    }

    printf("---------------------------------------------------------------\n");
}

void ispis_proizvoda(PROIZVOD* proizvodi, int broj_proizvoda) {
    printf("\nPopis proizvoda:\n");
    printf("SKU     \tNaziv       \tStanje       \tCijena   \tKategorija\n");

    for (int i = 0; i < broj_proizvoda; i++) {
        printf("%-8d\t%-12s\t%-12d\t%-8d\t%s\n",
            proizvodi[i].sku,
            proizvodi[i].ime,
            proizvodi[i].kolicina,
            proizvodi[i].cijena,
            proizvodi[i].kategorija);
    }
    printf("\n");
}
//********************************************BRISANJE PROIZVODA***************************************************//
void obrisi_proizvod() {
    int sku;
    printf("Unesite SKU proizvoda za brisanje: ");
    scanf("%d", &sku);

    FILE* datoteka = fopen("proizvodi.bin", "rb+");
    if (datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku.");
        return;
    }

    int broj_proizvoda = 0;
    fread(&broj_proizvoda, sizeof(int), 1, datoteka);
    if (broj_proizvoda == 0) {
        printf("Nema dostupnih proizvoda.\n");
        fclose(datoteka);
        return;
    }

    PROIZVOD* proizvodi = (PROIZVOD*)malloc(broj_proizvoda * sizeof(PROIZVOD));
    if (proizvodi == NULL) {
        printf("Nedovoljno memorije.");
        fclose(datoteka);
        return;
    }

    fread(proizvodi, sizeof(PROIZVOD), broj_proizvoda, datoteka);

    int indeks = -1;
    for (int i = 0; i < broj_proizvoda; i++) {
        if (proizvodi[i].sku == sku) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        printf("Proizvod s unesenim SKU brojem nije pronaden.\n");
        free(proizvodi);
        fclose(datoteka);
        return;
    }

    // Pomakni proizvode nakon obrisanog proizvoda
    for (int i = indeks; i < broj_proizvoda - 1; i++) {
        proizvodi[i] = proizvodi[i + 1];
    }

    broj_proizvoda--;

    fseek(datoteka, 0, SEEK_SET);
    fwrite(&broj_proizvoda, sizeof(int), 1, datoteka);
    fwrite(proizvodi, sizeof(PROIZVOD), broj_proizvoda, datoteka);

    printf("Proizvod je uspjesno obrisan.\n");

    free(proizvodi);
    fclose(datoteka);
}