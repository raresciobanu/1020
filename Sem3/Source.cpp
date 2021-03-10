#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum CULORI {
	ROZ,
	ALB = 10,
	VERDE,
	MARO,
	ALBASTRU,
	ROSU,
	GALBEN,
	PORTOCALIU
};

const char* afisareCuloare(CULORI culori) {
	switch (culori)
	{
	case ROZ:
		return "roz";
	case ALB:
		return "alb";
	case VERDE:
		return "verde";
	case MARO:
		return "maro";
	case ALBASTRU:
		return "albastru";
	case ROSU:
		return "rosu";
	case GALBEN:
		return "galben";
	case PORTOCALIU:
		return "portocaliu";
	default:
		break;
	}
}

CULORI transformaCuvantInEnum(const char* culoare) {
	if (strcmp(culoare, "roz")) {
		return CULORI::ROZ;
	}
	if (strcmp(culoare, "alb")) {
		return CULORI::ALB;
	}
	if (strcmp(culoare, "verde")) {
		return CULORI::VERDE;
	}
	if (strcmp(culoare, "maro")) {
		return CULORI::MARO;
	}
	if (strcmp(culoare, "albastru")) {
		return CULORI::ALBASTRU;
	}
	if (strcmp(culoare, "rosu")) {
		return CULORI::ROSU;
	}
	if (strcmp(culoare, "galben")) {
		return CULORI::GALBEN;
	}
	if (strcmp(culoare, "portocaliu")) {
		return CULORI::PORTOCALIU;
	}
}

union user
{
	int varsta;
	char nume[40];
	char gen;//M sau F
};

struct client {
	char nume[50];
	int varsta;
};

struct telefon
{
	CULORI culoareTelefon;
	char* marca;
	double pret;
	int anFabricatie;
	char marime;
	bool android;
	client proprietarTelefon;
};

void afisareClient(client c) {
	printf("nume client = %s\n", c.nume);
	printf("varsta = %d\n", c.varsta);
}

void afisareTelefon(telefon t) {
	printf("marca = %s\n", t.marca);
	printf("pret = %.2lf\n", t.pret);
	printf("anFabricatie = %d\n", t.anFabricatie);
	printf("marime = %c\n", t.marime);
	printf("sistem android = %s\n", t.android == 1 ? "true" : "false");

	afisareClient(t.proprietarTelefon);
	printf("culoare telefon = %s", afisareCuloare(t.culoareTelefon));
}

void scriereClientInFisier(FILE* fisier, client c) {
	fprintf(fisier, "%s\n", c.nume);
	fprintf(fisier, "%d\n", c.varsta);
}

void scriereTelefonInFisier(FILE* fisier, telefon t) {
	fprintf(fisier, "%s\n", t.marca);
	fprintf(fisier, "%.2lf\n", t.pret);
	fprintf(fisier, "%d\n", t.anFabricatie);
	fprintf(fisier, "%c\n", t.marime);
	fprintf(fisier, "%s\n", t.android == 1 ? "true" : "false");

	scriereClientInFisier(fisier, t.proprietarTelefon);
	fprintf(fisier, "%s\n", afisareCuloare(t.culoareTelefon));
}

void citireClientDinFisier(FILE* fisier, client& c) {
	fgetc(fisier);
	fgets(c.nume, 100, fisier);
	c.nume[strcspn(c.nume, "\n")] = 0;//pentru a scapa de \n cand citesti cu fgets

	fscanf(fisier, "%d", &c.varsta);
}

void citireTelefonDinFisier(FILE* fisier, telefon& t) {
	char aux[100];
	fscanf(fisier, "%s", &aux);
	t.marca = (char*)malloc((strlen(aux) + 1) * sizeof(char)); // '\0'
	strcpy(t.marca, aux);

	fscanf(fisier, "%lf", &t.pret);
	fscanf(fisier, "%d", &t.anFabricatie);
	fscanf(fisier, " %c", &t.marime); //se pune un spatiu inainte de %c pentru a citi cum trebuie din fisier...inainte se citea un \n de dupa anFabricatie

	fscanf(fisier, "%s", &aux);
	if (strcmp(aux, "true") == 0) {
		t.android = 1;
	}
	else {
		t.android = false;
	}

	citireClientDinFisier(fisier, t.proprietarTelefon);

	char culoare[100];
	fscanf(fisier, "%s", &culoare);
	t.culoareTelefon = transformaCuvantInEnum(culoare);
}

void scriereTelefoaneInFisierBinar(FILE* fisier, telefon t) {
	//functia fwrite - primeste ca input ===> fwrite(addressData, sizeData, numbersData, pointerToFile);
	//addressData - adresa variabilei citite (cu "&" in fata)
	//sizeData - dimensiunea variabilei salvate (sizeof)
	//numbersData - numarul de variabile salvate
				//int arr[3] = {101, 203, 303};
				// 
				//fwrite(arr, sizeof(int), 2, fp); //va scrie primele 2 elemente din vector
	//pointerToFile - fisierul unde se salveaza variabila, adica:  fisierBinarOut

	//DACA scrierea are erori atunci fwrite va retuna un numar mai mic decat variabila numbersData;

	///fwrite(&t, sizeof(l), 1, fisier); //daca nu aveam char* scriam asa.

	char aux[100];
	strcpy(aux, t.marca);
	fwrite(&aux, sizeof(aux), 1, fisier);

	fwrite(&t.pret, sizeof(t.pret), 1, fisier);
	fwrite(&t.anFabricatie, sizeof(t.anFabricatie), 1, fisier);
	fwrite(&t.marime, sizeof(t.marime), 1, fisier);

	if (t.android == 1) {
		strcpy(aux, "true");
	}
	else {
		strcpy(aux, "false");
	}
	fwrite(&aux, sizeof(aux), 1, fisier);

	fwrite(&t.proprietarTelefon, sizeof(t.proprietarTelefon), 1, fisier);

	strcpy(aux, afisareCuloare(t.culoareTelefon));
	fwrite(&aux, sizeof(aux), 1, fisier);
}

void citireTelefoanDinFisierBinar(FILE* fisier, telefon& t) {
	//functia fread - primeste ca input===> fread(addressData, sizeData, numbersData, pointerToFile);
	//descrierea parametrilor este la fel ca la fwrite

	//fread(&l, sizeof(l), 1, fisier); //daca nu aveam char* scriam asa.

	char aux[100];
	fread(&aux, sizeof(aux), 1, fisier);
	t.marca = (char*)malloc((strlen(aux) + 1) * sizeof(char));
	strcpy(t.marca, aux);

	fread(&t.pret, sizeof(t.pret), 1, fisier);
	fread(&t.anFabricatie, sizeof(t.anFabricatie), 1, fisier);
	fread(&t.marime, sizeof(t.marime), 1, fisier);

	fread(&aux, sizeof(aux), 1, fisier);
	if (strcmp(aux, "true") == 0) {
		t.android = 1;
	}
	else {
		t.android = 0;
	}

	fread(&t.proprietarTelefon, sizeof(t.proprietarTelefon), 1, fisier);

	fread(&aux, sizeof(aux), 1, fisier);
	t.culoareTelefon = transformaCuvantInEnum(aux);
}

void main() {
	CULORI c = CULORI::MARO;
	printf("culoare c=%d\n", c);

	user u;

	u.varsta = 100;
	printf("user varsta=%d\n", u.varsta);

	u.gen = 'M';
	printf("user gen=%c\n", u.gen);

	strcpy(u.nume, "George");
	printf("user nume=%s\n", u.nume);

	const int w = 0; //cum se declara o variabila constanta

	client client1;
	strcpy(client1.nume, "Bogdan Popescu");
	client1.varsta = 20;

	telefon t1;
	t1.android = true;
	t1.anFabricatie = 2020;
	t1.culoareTelefon = CULORI::ROSU;
	t1.marime = 'X';
	t1.marca = (char*)malloc((strlen("Huawei") + 1) * sizeof(char)); // '\0' 
	strcpy(t1.marca, "Huawei");
	t1.pret = 3999.99;
	t1.proprietarTelefon = client1;

	printf("\n\nAfisare telefon\n\n");
	afisareTelefon(t1);


	//scriere in fisier

	//w-creare fisier si scriere in el, daca exista fisierul se sterg toate informatiile din el
	//wb-este "w" in mod binar

	//r-citire din fisier, daca fisierul nu exista se intoarce NULL la fopen()
	//rb-este "r" in mod binar, daca fisierul nu exista se intoarce NULL la fopen()

	//a-adaugare informatii la sf fisierului, daca NU exista fisierul se face unul nou
	//ab- este "a" in mod binar

	//r+ sau rb+ - fisier deschis pentru citire si scriere/ citire si scriere in mod binar, daca fisierul nu exista se intoarce NULL la fopen()

	//w+ sau wb+ - fisier deschis pentru citire si scriere in mod binar. 

	//a+ si ab+ - fisier deschis pentru citire si adaugare la final

	FILE* fisier = fopen("telefoane.txt", "w");
	if (fisier == NULL) {
		printf("ERROR: telefoane.txt nu a fost deschis pentru scriere\n");
		exit(1);
	}
	printf("\n\nS-a scris ceva in fisierul text\n\n");

	scriereTelefonInFisier(fisier, t1);
	fclose(fisier);


	FILE* fisier2 = fopen("telefoane.txt", "r");
	if (fisier2 == NULL) {
		printf("ERROR: telefoane.txt nu a putut fi deschis pentru citire\n");
		exit(1);
	}
	printf("\n\nSe citeste ceva din fisierul text telefoane.txt\n\n");


	telefon t2;
	citireTelefonDinFisier(fisier2, t2);

	afisareTelefon(t2);

	fclose(fisier2);

	// ==== Scriere si citire din fisier binar ====
	FILE* fisierBinar = fopen("telefoaneBinar.bin", "wb");
	if (fisierBinar == NULL) {
		printf("ERROR: telefoaneBinar.bin nu a fost deschis pentru scriere\n");
		exit(1);
	}
	printf("\n\nS-a scris ceva in fisierul binar");

	scriereTelefoaneInFisierBinar(fisierBinar, t2);
	fclose(fisierBinar);



	FILE* fisierBinar2 = fopen("telefoaneBinar.bin", "rb");
	if (fisierBinar2 == NULL) {
		printf("ERROR: telefoaneBinar.bin nu a putut fi deschis pentru citire\n");
		exit(1);
	}
	printf("\n\nSe citeste ceva din fisierul binar telefoaneBinar.bin\n\n");


	telefon t4;
	citireTelefoanDinFisierBinar(fisierBinar2, t4);

	afisareTelefon(t4);

	fclose(fisierBinar2);

	free(t1.marca);
	free(t2.marca);
	free(t4.marca);



	FILE* fisierTxt = fopen("telefoane.txt", "r");
	if (fisierTxt == NULL) {
		printf("ERROR: telefoane.txt nu a putut fi deschis pentru citire\n");
		exit(1);
	}
	printf("\n\nSe citeste ceva din fisierul text telefoane.txt print functia feof\n\n");

	char aux[100];

	fscanf(fisierTxt, "%s", &aux);
	while (!feof(fisierTxt)) {
		printf("%s\n", aux);

		fscanf(fisierTxt, "%s", &aux) ;
	}

	rewind(fisierTxt);

	printf("\n === REWIND === \n\n");

	fscanf(fisierTxt, "%s", &aux);
	while (!feof(fisierTxt)) {
		printf("%s\n", aux);

		fscanf(fisierTxt, "%s", &aux);
	}


	fclose(fisierTxt);
}