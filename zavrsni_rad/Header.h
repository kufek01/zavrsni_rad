#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H

#define MAX_PROIZVODA 200
#define FILENAME "proizvodi.txt"

struct Proizvod {
    int sku;
    char naziv[50];
    int stanje;
};

struct Narudzba {
    int sku;
    char naziv[50];
    int kolicina;
};

void ispis_izbornika_vlasnik();
void ispis_izbornika_kupac();
void pregled_proizvoda();
void dodaj_proizvod();
void ucitaj_iz_datoteke();
void izmjena_stanja();
void nova_narudzba();
void sortiraj_proizvode();
void usporedi_po_imenu();
void usporedi_po_sku();

#endif