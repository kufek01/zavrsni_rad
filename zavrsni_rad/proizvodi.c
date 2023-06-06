#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

struct Proizvod proizvodi[MAX_PROIZVODA];
int broj_proizvoda = 0;

void pocetni_izbornik() {
	printf("Dobrodosli u webshop Kadar!\n");
	printf("-----------------------------\n");
	printf("Unesite svoju ulogu:\n");
	printf("-----------------------------\n");
	printf("1. Vlasnik\n");
	printf("-----------------------------\n");
	printf("2. Kupac\n");
	printf("-----------------------------\n");
	printf("Odaberite vasu ulogu: ");
}

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
	printf("SKU  \tNaziv  \tStanje  \n");


	FILE* datoteka = fopen("popis_proizvoda.bin", "rb");
	if (datoteka == NULL) {
		printf("Nije moguće otvoriti datoteku.");
		return;
	}

	struct Proizvod ucitani_proizvod;
	int broj_ucitanih_proizvoda = 0;

	while (fread(&ucitani_proizvod, sizeof(struct Proizvod), 1, datoteka) == 1) {
		printf("%d\t%s\t%d\n", ucitani_proizvod.sku, ucitani_proizvod.naziv, ucitani_proizvod.stanje);
		broj_ucitanih_proizvoda++;
	}

	fclose(datoteka);

	if (broj_ucitanih_proizvoda == 0) {
		printf("Nema dostupnih proizvoda.\n");
		return;
	}
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

	FILE* datoteka = fopen("popis_proizvoda.bin", "ab");
    if (datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku.");
        return;
    }

    fprintf(datoteka, "SKU: %d\n", novi_proizvod.sku);
    fprintf(datoteka, "Naziv: %s\n", novi_proizvod.naziv);
    fprintf(datoteka, "Stanje: %d\n\n", novi_proizvod.stanje);

    fclose(datoteka);
    printf("Proizvod uspjesno dodan.\n");
}


void ucitaj_iz_datoteke() {
        FILE* datoteka = fopen("popis_proizvoda.bin", "rb");
        if (datoteka == NULL) {
            printf("Nije moguce otvoriti datoteku.\n");
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
		FILE* datoteka = fopen("popis_proizvoda.bin", "wb");
        if (datoteka == NULL) {
            printf("Nije moguce otvoriti datoteku.");
            return;
        }

        for (int i = 0; i < broj_proizvoda; i++) {
            fprintf(datoteka, "SKU: %d\n", proizvodi[i].sku);
            fprintf(datoteka, "Naziv: %s\n", proizvodi[i].naziv);
            fprintf(datoteka, "Stanje: %d\n\n", proizvodi[i].stanje);
            printf("SKU: %d\tNaziv: %s\tStanje: %d\n", proizvodi[i].sku, proizvodi[i].naziv, proizvodi[i].stanje);
        }

        fclose(datoteka);

        printf("Stanje proizvoda uspjesno izmijenjeno.\n");
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
				system("cls");
                printf("Nedovoljna kolicina proizvoda na stanju.\n");
                return;
            }
        }
    }

    if (pronaden) {
		FILE* datoteka = fopen("popis_proizvoda.bin", "wb");
        if (datoteka == NULL) {
			system("cls");
            printf("Nije moguće otvoriti datoteku.");
            return;
        }

        for (int i = 0; i < broj_proizvoda; i++) {
            fprintf(datoteka, "SKU: %d\n", proizvodi[i].sku);
            fprintf(datoteka, "Naziv: %s\n", proizvodi[i].naziv);
            fprintf(datoteka, "Stanje: %d\n\n", proizvodi[i].stanje);
        }

        fclose(datoteka);
		system("cls");
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
		sortiraj_po_imenu();
		break;
	case 2:
		sortiraj_po_sku();
		break;
	default:
		printf("Neispravan odabir.\n");
		return;
	}

	printf("Proizvodi uspješno sortirani.\n");

	if (azuriraj_datoteku() != 0) {
		printf("Pogreška pri ažuriranju datoteke.\n");
	}
}

void sortiraj_po_imenu() {
	for (int i = 0; i < broj_proizvoda - 1; i++) {
		for (int j = 0; j < broj_proizvoda - i - 1; j++) {
			if (strcmp(proizvodi[j].naziv, proizvodi[j + 1].naziv) > 0) {
				struct Proizvod temp = proizvodi[j];
				proizvodi[j] = proizvodi[j + 1];
				proizvodi[j + 1] = temp;
			}
		}
	}
}

void sortiraj_po_sku() {
	for (int i = 0; i < broj_proizvoda - 1; i++) {
		for (int j = 0; j < broj_proizvoda - i - 1; j++) {
			if (proizvodi[j].sku > proizvodi[j + 1].sku) {
				struct Proizvod temp = proizvodi[j];
				proizvodi[j] = proizvodi[j + 1];
				proizvodi[j + 1] = temp;
			}
		}
	}
}

int azuriraj_datoteku() {
	FILE* datoteka = fopen("popis_proizvoda.bin", "wb");
	if (datoteka == NULL) {
		return -1; 
	}

	fwrite(proizvodi, sizeof(struct Proizvod), broj_proizvoda, datoteka);

	fclose(datoteka);
	return 0;
}

