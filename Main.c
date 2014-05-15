#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ------------------------------------------------------------------------- *
*	Dynamic arrays + structures + files                                      *
*   Written in C                                                             *
*          by Kl�vs Ceic�ns P2-4                                             *
*         	(Github - Kefirchiks | https://github.com/Kefirchiks )           *
* -------------------------------------------------------------------------- *
*	SHARING IS CARING                                                        *
* -------------------------------------------------------------------------- *
*	Izveidot dinamisko mas�vu no strukt�r�m.                                 *
*	Katra strukt�ra sast�v no minumums 4 laukiem, starp kuriem               *
*	oblig�ti ir ID lauks.                                                    *
*		Uz nodo�anas br�di - mas�v� j�b�t minimums 5 ierakstiem.             *
*	J�b�t iesp�jai:                                                          *
*			1. Pievienot ierakstus                                           *
*			2. Mekl�t p�c pamatvien�bas                                      *
*			3. Dz�st noteiktu ierakstu                                       *
*			4. Apskat�t DB saturu                                            *
*			5. Izpild�t individu�lo uzdevumu                                 *
* -------------------------------------------------------------------------- *
*	Individu�lais uzdevums                                                   *
*		Pamatvien�ba - uzv�rds                                               *
*		Atrast visus vad�t�jus, kuri vada konkr�tas firmas auto				 *
* -------------------------------------------------------------------------- */

typedef struct {    // Strukt�ra ar inform�ciju par vad�t�jiem
	unsigned short id;
	char uzv[15];
	char var[15];
	char autoMarka[20];
	signed short vecums;
} vad;

short skaits; // Ierakstu skaits
FILE *f; // Faila pl�smas variablis
vad *pas; // Nor�de uz strukt�ru (DB veido�anai)

void izdruka(void); // F-ja, kas izdruk� datubazes saturu
void pievienosana(void); // F-ja, kas pievieno ierakstu DB
void dzesana(void); // F-ja, kas dz�� ierakstu no DB
void atlasisana(void); // F-ja, kas atlasa visus vad�t�jus p�c uzv�rda
void individ(void);
// F-ja, kas izvada visus vad�t�jus, kuri vada konkr�tas markas auto
void saglabasana(void); // F-ja, kas saglaba izmainas datubaze

main(void) {
	int i;
	char izvele; // MENU

	f = fopen("db.dat", "a+b");
	fread(&skaits, sizeof(skaits), 1, f);
	// No faila tiek nolas�ts ierakstu daudzums

	pas = (vad*) malloc(skaits*sizeof(vad));
	if ((pas == NULL) && (skaits != 0)) {
		system("CLS");
		printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
		getch();
		return 0;
	}

	for (i = 0; i < skaits; i++)
		fread(&pas[i], sizeof(vad), 1, f); // Tiek nolas�ti ieraksti no faila
	fclose(f);

	do {
		system("CLS");
		printf("\nDATU BAZE: VADITAJI");
		printf("\n********************************");
		printf("\n1) Apskatit DATU BAZES saturu");
		printf("\n2) Pievienot ierakstu");
		printf("\n3) Dzest konkretu ierakstu");
		printf("\n4) Tiek meklets vaditajs pec uzvarda");
		printf("\n5) Izpildit individualo uzdevumu");
		printf("\n6) Saglabat izmainas");
		printf("\n7) Iziet");

		izvele = getch();
		switch (izvele) {
		case '1': // Izdruk�t DB saturu
			izdruka();
			break;
		case '2': // Pievienot jaunu ierakstu DB
			pievienosana();
			break;
		case '3': // Dz�st ierakstu no DB
			dzesana();
			break;
		case '4': // Mekl�t vad�t�ju p�c uzv�rda
			atlasisana();
			break;
		case '5': // Individu�lais uzdevums
			individ();
			break;
		case '6': // Saglab�t izmai�as (fail�)
			saglabasana();
			break;
		}
	}
	while (izvele != '7');
	free(pas);
}
// ==============================================================================
// Funkcija DB izdrukai
// ==============================================================================
void izdruka(void) {
	int i;

	system("CLS");

	printf("|ID|");
	printf("       |Uzvards");
	printf("       |Vards");
	printf("         |Auto ");
	printf("		     |Vecums|\n");
	printf(" -------------------------------------------------------------------\n"
		);
	for (i = 0; i < skaits; i++) {
		printf("|%hd|        ", pas[i].id);
		printf("|%s", pas[i].uzv);
		printf("|%s", pas[i].var);
		printf("|%s", pas[i].autoMarka);
		printf("|%hd    |\n", pas[i].vecums);
	}
	printf(" -------------------------------------------------------------------\n"
		);

	getch();
}
// ==============================================================================
// Funkcija ieraksta pievieno�anai
// ==============================================================================
void pievienosana(void) {
	int i;
	char tmpuv[30], pasuv[30]; // Uzvards + vards, sakartosanai alfabeta seciba
	char tmps[20] = "                   "; // Variablis lauku aizpild��anai
	vad pastmp; // Temporary variablis - ierakstu pievieno�anai

	system("CLS");
	++skaits;

	pas = (vad*)realloc(pas, skaits*sizeof(vad)); // Rezerv�ta atmi�a priek� DB
	if ((pas == NULL) && (skaits != 0)) {
		system("CLS");
		printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
		getch();
	}

	if (skaits == 1) { // Ja DB ir tuk�a, tad vienk�r�i pievieno ierakstu
		printf("Uzvards: ");
		scanf("%s", &pas[skaits - 1].uzv);
		strncat(pas[skaits - 1].uzv, tmps, 14 - strlen(pas[skaits - 1].uzv));
		printf("Vards: ");
		scanf("%s", &pas[skaits - 1].var);
		strncat(pas[skaits - 1].var, tmps, 14 - strlen(pas[skaits - 1].var));
		printf("Auto: ");
		scanf("%s", &pas[skaits - 1].autoMarka);
		strncat(pas[skaits - 1].autoMarka, tmps,
			19 - strlen(pas[skaits - 1].autoMarka));
		printf("Vecums: ");
		scanf("%hd", &pas[skaits - 1].vecums);
	}
	else // Ja nav tuk�a, tad sak�rto DB alfab�ta sec�b�
	{
		printf("Uzvards: ");
		scanf("%s", &pastmp.uzv);
		strncat(pastmp.uzv, tmps, 14 - strlen(pastmp.uzv));
		printf("Vards: ");
		scanf("%s", &pastmp.var);
		strncat(pastmp.var, tmps, 14 - strlen(pastmp.var));
		printf("Auto: ");
		scanf("%s", &pastmp.autoMarka);
		strncat(pastmp.autoMarka, tmps, 19 - strlen(pastmp.autoMarka));
		printf("Vecums: ");
		do
			scanf("%hd", &pastmp.vecums);
		while (pastmp.vecums < 1);

		strcpy(tmpuv, "");
		strcat(tmpuv, pastmp.uzv);
		strcat(tmpuv, pastmp.var);
		i = skaits - 1;
		do { // Sak�rto alfab�ta sec�b� p�c uzv�rda
			--i;
			if (i < 0)
				break;
			pas[i + 1] = pas[i];
			strcpy(pasuv, "");
			strcat(pasuv, pas[i].uzv);
			strcat(pasuv, pas[i].var);
		}
		while (strcmpi(tmpuv, pasuv) < 0);

		pas[i + 1] = pastmp;
	}

	for (i = 0; i < skaits; i++)
		pas[i].id = i + 1; // P�c DB sak�rto�anas
	// no jauna pie��ir ierakstiem ID
}
// ==============================================================================
// Funkcija ieraksta dz��anai
// ==============================================================================
void dzesana(void) {
	int i;
	short *id; // Dinamiskais mas�vs ar ID laukiem
	short error; // P�rbauda vai tika ievad�ts pareizs ID
	short tmp, tmp2; // TMP mainigie, vairaku uzdevumu pildisanai
	char uzvards[15]; // Lietotaja ievadamais uzvards, uzvardu salidzinasanai
	char tmps[20] = "                   ";
	// Laicigais mainigais, ierakstu pievienosanai

	system("CLS");
	printf("IEVADIET VADITAJA UZVARDU, KURU JUS GRIBAT DZEST NO DATUBAZES.\n");
	printf("Uzvards = ");
	scanf("%s", &uzvards);
	strncat(uzvards, tmps, 14 - strlen(uzvards));
	printf("\n");

	tmp = 0;
	id = (short*)malloc(tmp*sizeof(short)); // Rezerv� atmi�u
	if ((id == NULL) && (tmp != 0)) {
		system("CLS");
		printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
		getch();
	}

	for (i = 0; i < skaits; i++) {
		if (strcmpi(uzvards, pas[i].uzv) == 0)
		{ // Sal�dzina ievad�to ar DB eso�o
			tmp++;
			printf("ID: %hd\n", pas[i].id);
			printf("Uzvards: %s\n", pas[i].uzv);
			printf("Vards: %s\n", pas[i].var);
			printf("Auto: %s\n", pas[i].autoMarka);
			printf("Vecums: %hd\n\n", pas[i].vecums);
			printf("***\n\n");
			id = (short*)realloc(id, tmp*sizeof(short));
			if ((id == NULL) && (tmp != 0)) {
				system("CLS");
				printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
				getch();
			}

			id[tmp - 1] = pas[i].id;
		}
	}

	error = 1;
	if (tmp != 0) {
		do { // Programma pied�v� ievad�t ID, kuru dz�st, kam�r
			// tiek ievadits at�autais ID (no ierakstiem, kurus atrad�m)
			printf("IEVADIET IERAKSTA ID, KURU GRIBAT DZEST\n");
			printf("ID = ");
			scanf("%hd", &tmp2);

			for (i = 0; i < tmp; i++) // P�rbauda vai tika ievad�ts pareizais ID
				if (tmp2 == id[i])
					error = 0;
				else if (i == (tmp - 1))
					printf("\nTIKA IEVADITS NEPAREIZS ID\n\n");

		}
		while (error != 0);

		for (i = (tmp2 - 1); i < (skaits - 1); i++)
		{ // Dz��anas gad�jum� sak�rto DB
			pas[i] = pas[i + 1];
			pas[i].id -= 1;
		}

		--skaits;
		pas = (vad*)realloc(pas, skaits*sizeof(vad));
		if ((pas == NULL) && (skaits != 0)) {
			system("CLS");
			printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
			getch();
		}

	}
	else {
		printf("UZVARDS PEC JUSU PIEPRASIJUMA NETIKA ATRASTS");
		getch();
	}

	free(id);
}
// ==============================================================================
// Funkcija vad�t�ju atlas��anai
// ==============================================================================
void atlasisana(void) {
	int i;
	short tmp; // TMP variablis
	char uzvards[15]; // Uzv�rda variablis sal�dzin��anai
	char tmps[20] = "                   ";
	// TMP variablis - ierakstu pievieno�anai

	system("CLS");
	printf("IEVADIET VADITAJA UZVARDU\n");
	printf("Uzvards = ");
	scanf("%s", &uzvards);
	strncat(uzvards, tmps, 14 - strlen(uzvards));
	printf("\n\n");

	tmp = 0;
	for (i = 0; i < skaits; i++) { // Mekl� vad�t�jus ar konkr�tu uzv�rdu
		if (strcmpi(uzvards, pas[i].uzv) == 0) { // Sal�dzina ar DB datiem
			printf("ID: %hd\n", pas[i].id);
			printf("Uzvards: %s\n", pas[i].uzv);
			printf("Vards: %s\n", pas[i].var);
			printf("Auto: %s\n", pas[i].autoMarka);
			printf("Vecums: %hd\n\n", pas[i].vecums);
			printf("***\n\n");
			tmp++;
		}
	}

	if (tmp == 0)
		printf("UZVARDS PEC JUSU PIEPRASIJUMA NETIKA ATRASTS");

	getch();
}
// ==============================================================================
// Funkcija visu auto marku vad�t�ju atlasei
// ==============================================================================
void individ(void) {
	int i;
	char aut[20]; // Auto marku sal�dzin��anai
	short tmp; // Temporary variablis
	char tmps[20] = "                   "; // TMP variablis

	system("CLS");
	printf("IEVADIET AUTO FIRMU, PEC KURA ATLASIT VADITAJUS.\n");
	printf("Auto = ");
	scanf("%s", &aut);
	strncat(aut, tmps, 19 - strlen(aut));
	printf("\n");

	tmp = 0;
	for (i = 0; i < skaits; i++)
	{ // Tiek mekl�ti vad�t�ji, kuri vada konkr�tas markas auto
		if (strcmpi(aut, pas[i].autoMarka) == 0)
		{ // Sal�dzina ievad�tos datus ar DB
			printf("ID: %hd\n", pas[i].id);
			printf("Uzvards: %s\n", pas[i].uzv);
			printf("Vards: %s\n", pas[i].var);
			printf("Auto: %s\n", pas[i].autoMarka);
			printf("Vecums: %hd\n\n", pas[i].vecums);
			printf("***\n\n");
			tmp++;
		}
	}

	if (tmp == 0)
		printf("AUTO FIRMA PEC JUSU PIEPRASIJUMA NETIKA ATRASTA");

	getch();
}
// ==============================================================================
// Funkcija DB saglab��anai
// ==============================================================================
void saglabasana(void) {
	int i;

	system("CLS");
	printf("DATU BAZE TIKA VEIKSMIGI SAGLABATA");
	f = fopen("db.dat", "wb");
	fwrite(&skaits, sizeof(short), 1, f);
	for (i = 0; i < skaits; i++) { // Saglab�jam fail�
		fwrite(&pas[i], sizeof(vad), 1, f);
		pas[i].id = i + 1;
	}
	fclose(f);

	getch();
}
