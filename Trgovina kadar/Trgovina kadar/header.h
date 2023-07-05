#ifndef TRGOVINA_H
#define TRGOVINA_H

typedef struct proizvod {
	int sku;
	char kategorija[25];
	char ime[25];
	int cijena;
	int kolicina;
}PROIZVOD;

void ispis_izbornika_vlasnik();
void ispis_izbornika_kupac();
void* pregled_proizvoda();
void dodaj_proizvod();
void izmjena_stanja();
void nova_narudzba();
int sortiraj_proizvode();
void najjeftinije_do_najskuplje();
void najskuplje_do_najjeftinije();
void ispis_proizvoda();
void obrisi_proizvod();


#endif // HEADER_H