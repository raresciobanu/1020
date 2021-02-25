#include<stdio.h> //librarie folosita pentru citire si afisare
#include<math.h> //librarie folosita pentru functii matematice
#include<stdlib.h> //librarie pentru crearea/dezalocarea pointerilor

//metoda bisectiei
//Sa se rezolve ecuatiile 1,2,3 prin metoda bisectiei

void test1(int &x) {
	x++;
}

double ecuatie1(double x) {
	return 3 * pow(x, 3) - 2 * pow(x, 2) + 10 * x + 30;
}

double ecuatie2(double x) {
	return 3 * x - 9;
}

double ecuatie3(double x) {
	return 3 * pow(x, 2) - 3 * x - 1;
}


void metodaBisectiei(double A, double B, int N,
	double(*ptr_ecuatie)(double), double epsilon,
	double& solutie, int& cod) {//se pune "&" pentru ca variabilele cod si solutie se modifica in acest bloc si vrem sa primim valorile modificate si in main()

	//A,B - capetele intervalului in care se cauta radacina unica

	//N-numarul maxim de pasi de cautare(daca nu gasesti radicina in 1000 pasi te opresti...nu cauti la nesfarsit)

	//double(*ptr_ecuatie)(double) - pointer la functie -> folosita pentru a transmite mai departe ecuatiile de mai sus 1,2,3
	//daca va uitati atent pointerul la functie are acelasi format ca antetul functiilor de mai sus.

	//epsilon - eroarea acceptat - o variabila cat mai mica : 0.00001 

	//solutie - se va salva in variabila solutie valoarea radacinei
	//cod - poate fi 0 sau 1 ...-> 1 daca s-a gasit radacina, 0 altfel.

	solutie = cod = 0;

	if (ptr_ecuatie(A) == 0) { solutie = A; cod = 1; return; } //aici se verifica daca partea inferioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(B) == 0) { solutie = B; cod = 1; return; } //aici se verifica daca partea superioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(A) * ptr_ecuatie(B) > 0) {
		printf("Nu s-a gasit nicio radacina sau s-au gasit prea multe\n"); //aici e clar ce se intampla sper...
		cod = 0; return;
	}
	while (N > 0 && cod == 0) {///se itereaza in maxim N pasi sau pana cand se gaseste radacina
		solutie = (A + B) / 2; //ne pozitionam la mijlocul intervalului [A,B]

		if (ptr_ecuatie(solutie) == 0) { //daca valoarea de la mijlocul intervalului [A,B] este radacina atunci am gasit solutia.
			cod = 1; continue;
		}

		if (ptr_ecuatie(A) * ptr_ecuatie(solutie) < 0) {//daca nu s a gasit radacina mai sus atunci trebuie sa cautam alt interval
			B = solutie;//in cazul asta noul interval de cautare va fi [A,solutie] - (unde solutie era (A+B)/2)
		}
		else {
			A = solutie;//in cazul asta noul interval de cautare va fi [solutie, B] - (unde solutie era (A+B)/2)
		}

		if (B - A <= epsilon) {//se accepta o radacina x in care f(x) sa tinda catre 0......
			cod = 1;
		}

		N--;//se trece la urmatorul pas. daca nu se gaseste solutia in N pasi atunci codul ramane 0;
	}


}

int main() {
	//scriere la tastatura

	//1 bit poate avea valoarea 0 sau 1
	//un byte ocupa 8 biti
	printf("Un byte este format din 8 biti.\n\n");
	int x = 5; //var. intreaga - 4 bytes 
	double y = 4443.3321; //var. reala - 8 bytes
	float z = 20.2; //var. reala - 4 bytes
	char c = 'a'; //var. caracter - 1 byte

	printf("int ocupa: %d bytes.\n", sizeof(int));
	printf("double ocupa: %d bytes.\n", sizeof(double));
	printf("float ocupa: %d bytes.\n", sizeof(float));
	printf("char ocupa: %d bytes.\n", sizeof(char));

	//%d = format de afisare pentru int
	//%f = format de afisare pentru float
	//%lf = format de afisare pentru double
	//%c = format de afisare pentru char

	printf("\nx=%d\n", x);
	printf("\nx=%d  y=%lf  z=%f  c=%c\n", x, y, z, c);


	//citire de la tastatura
	int a, b;
	double u;
	/*printf("introdu o valoare pentru a: ");
	scanf_s("%d", &a);
	printf("afisare a=%d\n", a);*/

	//printf("b=");
	//scanf_s("%d", &b);
	//printf("afisare b=%d\n", b);

	//printf("u=");
	//scanf_s("%lf", &u);
	//printf("afisare u=%.2lf\n", u);



	int val = 129;
	int* pval = &val;

	printf("\n\nadresa lui val este: %p\n", &val);

	printf("pointerul pval are valoarea: %p\n", pval);

	printf("valoarea de la adresa &val este: %d\n\n", *pval);

	//int N;
	//printf("N=");
	//scanf_s("%d", &N);

	//int* vector = (int*)malloc(N * sizeof(int));
	
	//int* vector = (int*)realloc(vector, N * sizeof(int)); //realoc-folosit pt a realoca memoria existenta
	//int* vector = (int*)calloc(N, sizeof(int)); //calloc este folosit pt a aloca memorie ca si malloc + va seta toate elementele din vector = 0

	//for (int i = 0; i < N; i++) {
	//	printf("v[%d]=", i);
	//	scanf_s("%d", &vector[i]);
	//}

	//for (int i = 0; i < N; i++) {
	//	printf("v[%d]=%d ", i, vector[i]);
	//}

	int hh1 = 1000;
	test1(hh1);
	printf("hh1=%d\n", hh1);

	//pointer la functie pentru ecuatie 2
	double (*pointer_la_functie)(double);

	pointer_la_functie = ecuatie1;
	printf("ecuatie1 rezultat=%lf\n\n", (*pointer_la_functie)(2));

	pointer_la_functie = ecuatie2;
	printf("ecuatie2 rezultat=%lf\n\n", (*pointer_la_functie)(2));

	pointer_la_functie = ecuatie3;
	printf("ecuatie3 rezultat=%lf\n\n", (*pointer_la_functie)(2));


	//metoda bisectiei
	double solutie = 0;
	int cod = 0;
	metodaBisectiei(-2, 12, 1000, ecuatie1, 0.0001, solutie, cod);
	printf("ecuatie 1: cod=%d, solutie=%lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie2, 0.0001, solutie, cod);
	printf("ecuatie 2: cod=%d, solutie=%lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie3, 0.0001, solutie, cod);
	printf("ecuatie 3: cod=%d, solutie=%lf\n", cod, solutie);


	//dezalocare memorie pointer
	//free(vector);
}