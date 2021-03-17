#include<stdio.h>
#include<stdlib.h>

struct Animal {
	int key;
	char denumire[30];
	int varsta;
	double greutate;
	char culoare[20];
	int esteSetat;
};

void afisareAnimal(Animal a) {
	printf("Key=%d\n", a.key);
	printf("Denumire=%s\n", a.denumire);
	printf("Varsta=%d\n", a.varsta);
	printf("Greutate=%.2lf\n", a.greutate);
	printf("Culoare=%s\n", a.culoare);
	printf("EsteSetat=%d\n", a.esteSetat);
}

int aflaCateAnimaleSuntInFisier(FILE* f) {
	//ftell-> returneaza pozitia curenta in fisier
	int pozCurenta = ftell(f);//pastram pozitia curenta

	fseek(f, 0, SEEK_END);//se pozitioneaza la sf fisierului

	int nrAnimale = ftell(f) / sizeof(Animal);

	fseek(f, pozCurenta, SEEK_SET);//se pozitioneaza la pozitia initiala;

	return nrAnimale;
}
void main() {
	//Afisarea informatiilor in format tabel

	//FILE *f = fopen("ceva.txt", "w");
	//fprintf(f, "%4s %-16s %3s %30s", "Crt.", "BBB", "AAAA", "Suma");
	//printf("%4s %-16s %3s %30s", "Crt.", "BBB", "AAAA", "Suma");

	//fclose(f);


	//long int ftell(FILE *fp); - returneaza pozitia curenta;

	//int fseek(FILE *fp, long int offset, int origin);

	//fp - fisierul peste care se aplica operatia fseek;

	//offset - numarul de bytes fata de origine(al 3 lea parametru);
	//poate fi nr. pozitiv(pt mersul inainte prin fisier) sau negativ(pt mersul inapoi prin fisier);

	//origin - originea punctului fata de care se aplica offsetul; 
	//Ex: SEEK_SET - inceputul fisierului
	//Ex: SEEK_CUR - pozitia curenta a fisierului
	//Ex: SEEK_END - sfarsitul fisierului

	//fseek - returneaza 0 daca mutarea a fost efectuata cu succes, altfel o alta val !=0
	FILE* fisBin = fopen("fisAnimaleBinar.bin", "wb+");

	if (fisBin == NULL) {
		printf("ERROR: fisAnimaleBinar.bin nu s-a putut deschide.");
		exit(1); //sau return;
	}

	while (!feof(stdin)) {//atunci cand se cere: sfarsitul introducerii fiind marcat standard.

		printf("Alegeti o optiune din meniu:\n");
		printf("1) Salvati un animal in fisier la o anumita pozitie\n");
		printf("2) Modificati un animal din fisier de la o anumita pozitie\n");
		printf("3) Stergeti un animal din fisier de la o anumita pozitie\n");
		printf("4) Afisati un animal din fisier de la o anumita pozitie\n");
		printf("5) Exit.\n\n");

		int optiune = 0;
		printf("Introduceti optiunea dorita:\n");
		printf("optiune="); scanf("%d", &optiune);

		switch (optiune) {
		case 1: {
			//se citeste de la tastatura un nou animal
			Animal x;
			printf("Introduceti valorile dorite:\n");
			int key = 0;
			printf("key="); scanf("%d", &key);

			x.key = key;
			
			int nrAnimale = aflaCateAnimaleSuntInFisier(fisBin);

			if (x.key >= nrAnimale) {
				//alocam memorie noua daca cheia introdusa > nr de animale din fisier
				x.esteSetat = 0;
				fseek(fisBin, 0, SEEK_END);
				for (int i = 0; i < (x.key + 1) - nrAnimale; i++) {
					fwrite(&x, sizeof(Animal), 1, fisBin);
				}
			}

			//se pozitioneaza cursorul la adresa: x.key * sizeof(Animal)
			fseek(fisBin, x.key * sizeof(Animal), SEEK_SET);
			//se citeste animalul de la adresa: x.key * sizeof(Animal) 
			fread(&x, sizeof(Animal), 1, fisBin);
			x.key = key;

			if (x.esteSetat == 1) {
				printf("La cheia introdusa exista deja un animal. Nu se mai poate adauga unul.\n");
			}
			else {
				printf("Denumire="); scanf("%s", &x.denumire);
				printf("Varsta="); scanf("%d", &x.varsta);
				printf("Greutate="); scanf("%lf", &x.greutate);
				printf("Culoare="); scanf("%s", &x.culoare);
				x.esteSetat = 1;

				//se pozitioneaza cursorul la adresa: x.key * sizeof(Animal)
				fseek(fisBin, x.key * sizeof(Animal), SEEK_SET);
				//se scrie Animalul in fisier la adresa: x.key * sizeof(Animal)
				fwrite(&x, sizeof(Animal), 1, fisBin);
			}
			break;
		}
		case 2: {
			Animal x;
			printf("key="); scanf("%d", &x.key);

			//se pozitioneaza cursorul la adresa: x.key * sizeof(Animal)
			fseek(fisBin, x.key * sizeof(Animal), SEEK_SET);
			//se citeste animalul de la adresa: x.key * sizeof(Animal) 
			fread(&x, sizeof(Animal), 1, fisBin);

			if (x.esteSetat == 1) {
				printf("Denumire="); scanf("%s", &x.denumire);
				printf("Varsta="); scanf("%d", &x.varsta);
				printf("Greutate="); scanf("%lf", &x.greutate);
				printf("Culoare="); scanf("%s", &x.culoare);

				//se pozitioneaza cursorul la adresa: x.key * sizeof(Animal)
				fseek(fisBin, x.key * sizeof(Animal), SEEK_SET);
				//se scrie Animalul in fisier la adresa: x.key * sizeof(Animal)
				fwrite(&x, sizeof(Animal), 1, fisBin);
			}
			else {
				printf("LA cheia introdusa nu exista un animal definit.\n");
			}
			break;
		}
		case 3: {
			Animal x;
			printf("key="); scanf("%d", &x.key);

			//se pozitioneaza cursorul la adresa: x.key * sizeof(Animal)
			fseek(fisBin, x.key * sizeof(Animal), SEEK_SET);
			//se citeste animalul de la adresa: x.key * sizeof(Animal) 
			fread(&x, sizeof(Animal), 1, fisBin);

			if (x.esteSetat == 1) {
				x.esteSetat = 0;
				//ACTUALIZAM animalul

				//se pozitioneaza cursorul la adresa: x.key * sizeof(Animal)
				fseek(fisBin, x.key * sizeof(Animal), SEEK_SET);
				//se scrie Animalul in fisier la adresa: x.key * sizeof(Animal)
				fwrite(&x, sizeof(Animal), 1, fisBin);


				printf("S-a sters animalul de la adresa: %d.\n", x.key);
			}
			else {
				printf("LA cheia introdusa nu exista un animal definit.\n");
			}
			break;
		}
		case 4: {
			Animal x;
			printf("key="); scanf("%d", &x.key);

			//se pozitioneaza cursorul la adresa: x.key * sizeof(Animal)
			fseek(fisBin, x.key * sizeof(Animal), SEEK_SET);
			//se citeste animalul de la adresa: x.key * sizeof(Animal) 
			fread(&x, sizeof(Animal), 1, fisBin);

			if (x.esteSetat == 1) {
				afisareAnimal(x);
			}
			else {
				printf("LA cheia introdusa nu exista un animal definit.\n");
			}

			break;
		}
		case 5: {
			exit(1);
			break;
		}

		}

	}

	fclose(fisBin);
}