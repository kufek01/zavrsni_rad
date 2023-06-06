#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    int uloga;
    int izbor;
	int status = 0;

	do {
		pocetni_izbornik();
		scanf("%d", &uloga);

		if (uloga == 1) {
			do {
				ispis_izbornika_vlasnik();
				scanf("%d", &izbor);
				system("cls");

				switch (izbor) {
				case 1:
					pregled_proizvoda();
					break;
				case 2:
					dodaj_proizvod();
					break;
				case 3:
					izmjena_stanja();
					break;
				case 4:
					nova_narudzba();
					break;
				case 5:
					sortiraj_proizvode();
					break;
				case 6:
					ucitaj_iz_datoteke();
					break;
				case 7:
					break;
				case 0:
					printf("Hvala sto koristite Kadar trgovinu.\n");
					status = 1;
					return 0;
				default:
					printf("Nepoznata opcija. Molimo unesite ponovno.\n");
				}
			} while (izbor != 7);
		}
		else if (uloga == 2) {
			do {
				ispis_izbornika_kupac();
				scanf("%d", &izbor);

				switch (izbor) {
				case 1:
					nova_narudzba();
					break;
				case 2:
					pregled_proizvoda();
					break;
				case 3:
					break;
				case 0:
					printf("Hvala sto koristite nasu trgovinu.\n");
					return 0;
				default:
					printf("Nepoznata opcija. Molimo unesite ponovno.\n");
				}
			} while (izbor != 0);
		}
		
		else {
			printf("Nepoznata uloga. Pokusajte ponovno.\n");
		}
	} while (status == 0);

    return 0;
}