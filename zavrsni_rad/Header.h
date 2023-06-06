#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H

#define MAX_PROIZVODA 200
#define FILENAME "proizvodi.txt"

typedef struct Proizvod{
    int sku;
    char naziv[50];
    int stanje;

}PROIZVOD;

typedef struct Narudzba{
    int sku;
    char naziv[50];
    int kolicina;
}NARUDZBA;

void ispis_izbornika_vlasnik();
void ispis_izbornika_kupac();
void pregled_proizvoda();
void dodaj_proizvod();
void ucitaj_iz_datoteke();
void izmjena_stanja();
void nova_narudzba();
void sortiraj_proizvode();
void sortiraj_po_imenu();
void sortiraj_po_sku();
void pocetni_izbornik();

#endif