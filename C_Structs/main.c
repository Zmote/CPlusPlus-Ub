#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int artikelNummer;
	int anzahl;
	float preis;
	char bezeichnung[50];
}t_artikel;

void printArtikel(t_artikel artikel);

int main(){
	t_artikel artikel1 = {101,10,2.50,"Red Bull"};
	t_artikel artikel2 = {102,20,1.25,"Coca Cola"};
	printArtikel(artikel1);
	printArtikel(artikel2);
	return 0;
}

void printArtikel(t_artikel artikel){
	printf("Artikelnummer: %d\nAnzahl: %d\nPreis: %f\nBezeichnung: %s\n\n",
			artikel.artikelNummer,artikel.anzahl,artikel.preis,artikel.bezeichnung);
}