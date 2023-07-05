#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    int odabir_uloge;
    int odabir;
    int povratak = 0;

    do {
        povratak = 0;
        printf("Dobrodosli u webshop Kadar!\n");
        printf("-----------------------------\n");
        printf("Unesite svoju ulogu:\n");
        printf("-----------------------------\n");
        printf("1. Vlasnik\n");
        printf("-----------------------------\n");
        printf("2. Kupac\n");
        printf("-----------------------------\n");
        printf("Odaberite vasu ulogu: ");
        scanf("%d", &odabir_uloge);

        switch (odabir_uloge) {
        case 1:
            do {
                ispis_izbornika_vlasnik();
                scanf("%d", &odabir);
                switch (odabir) {
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
                    obrisi_proizvod();
                    break;
                case 7:
                    povratak = 1;
                    system("cls");
                    break;
                case 0:
                    odabir_uloge = 0;
                    printf("Izlaz iz programa.\n");
                    break;
                default:
                    printf("Pogresan unos.\n");
                    break;
                }
            } while (odabir != 0 && !povratak);
            break;
        case 2:
            do {
                ispis_izbornika_kupac();
                scanf("%d", &odabir);
                switch (odabir) {
                case 1:
                    pregled_proizvoda();
                    nova_narudzba();
                    break;
                case 2:
                    pregled_proizvoda();
                    break;
                case 3:
                    povratak = 1;
                    system("cls");
                    break;
                case 0:
                    odabir_uloge = 0;
                    printf("Izlaz iz programa.\n");
                    break;
                default:
                    printf("Pogresan unos.\n");
                    break;
                }
            } while (odabir != 0 && !povratak);
            break;
        case 0:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Pogresan unos.\n");
            break;
        }
    } while (odabir_uloge != 0);

    return 0;
}