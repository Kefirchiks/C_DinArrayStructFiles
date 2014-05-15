#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ------------------------------------------------------------------------- *
*	Dynamic arrays + structures + files                                      *
*   Written in C                                                             *
*          by Klâvs Ceicâns P2-4                                             *
*         	(Github - Kefirchiks | https://github.com/Kefirchiks )           *
* -------------------------------------------------------------------------- *
*	SHARING IS CARING                                                        *
* -------------------------------------------------------------------------- *
*	Izveidot dinamisko masîvu no struktûrâm.                                 *
*	Katra struktûra sastâv no minumums 4 laukiem, starp kuriem               *
*	obligâti ir ID lauks.                                                    *
*		Uz nodoðanas brîdi - masîvâ jâbût minimums 5 ierakstiem.             *
*	Jâbût iespçjai:                                                          *
*			1. Pievienot ierakstus                                           *
*			2. Meklçt pçc pamatvienîbas                                      *
*			3. Dzçst noteiktu ierakstu                                       *
*			4. Apskatît DB saturu                                            *
*			5. Izpildît individuâlo uzdevumu                                 *
* -------------------------------------------------------------------------- *
*	Individuâlais uzdevums                                                   *
*		Pamatvienîba - uzvârds                                               *
*		Atrast visus vadîtâjus, kuri vada konkrçtas firmas auto				 *
* -------------------------------------------------------------------------- */

typedef struct {    // Struktûra ar informâciju par vadîtâjiem
	unsigned short id;
	char uzv[15];
	char var[15];
	char autoMarka[20];
	signed short vecums;
} vad;

short skaits; // Ierakstu skaits
FILE *f; // Faila plûsmas variablis
vad *pas; // Norâde uz struktûru (DB veidoðanai)

void izdruka(void); // F-ja, kas izdrukâ datubazes saturu
void pievienosana(void); // F-ja, kas pievieno ierakstu DB
void dzesana(void); // F-ja, kas dzçð ierakstu no DB
void atlasisana(void); // F-ja, kas atlasa visus vadîtâjus pçc uzvârda
void individ(void);
// F-ja, kas izvada visus vadîtâjus, kuri vada konkrçtas markas auto
void saglabasana(void); // F-ja, kas saglaba izmainas datubaze

main(void) {
	int i;
	char izvele; // MENU

	f = fopen("db.dat", "a+b");
	fread(&skaits, sizeof(skaits), 1, f);
	// No faila tiek nolasîts ierakstu daudzums

	pas = (vad*) malloc(skaits*sizeof(vad));
	if ((pas == NULL) && (skaits != 0)) {
		system("CLS");
		printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
		getch();
		return 0;
	}

	for (i = 0; i < skaits; i++)
		fread(&pas[i], sizeof(vad), 1, f); // Tiek nolasîti ieraksti no faila
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
		case '1': // Izdrukât DB saturu
			izdruka();
			break;
		case '2': // Pievienot jaunu ierakstu DB
			pievienosana();
			break;
		case '3': // Dzçst ierakstu no DB
			dzesana();
			break;
		case '4': // Meklçt vadîtâju pçc uzvârda
			atlasisana();
			break;
		case '5': // Individuâlais uzdevums
			individ();
			break;
		case '6': // Saglabât izmaiòas (failâ)
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
// Funkcija ieraksta pievienoðanai
// ==============================================================================
void pievienosana(void) {
	int i;
	char tmpuv[30], pasuv[30]; // Uzvards + vards, sakartosanai alfabeta seciba
	char tmps[20] = "                   "; // Variablis lauku aizpildîðanai
	vad pastmp; // Temporary variablis - ierakstu pievienoðanai

	system("CLS");
	++skaits;

	pas = (vad*)realloc(pas, skaits*sizeof(vad)); // Rezervçta atmiòa priekð DB
	if ((pas == NULL) && (skaits != 0)) {
		system("CLS");
		printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
		getch();
	}

	if (skaits == 1) { // Ja DB ir tukða, tad vienkârði pievieno ierakstu
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
	else // Ja nav tukða, tad sakârto DB alfabçta secîbâ
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
		do { // Sakârto alfabçta secîbâ pçc uzvârda
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
		pas[i].id = i + 1; // Pçc DB sakârtoðanas
	// no jauna pieðíir ierakstiem ID
}
// ==============================================================================
// Funkcija ieraksta dzçðanai
// ==============================================================================
void dzesana(void) {
	int i;
	short *id; // Dinamiskais masîvs ar ID laukiem
	short error; // Pârbauda vai tika ievadîts pareizs ID
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
	id = (short*)malloc(tmp*sizeof(short)); // Rezervç atmiòu
	if ((id == NULL) && (tmp != 0)) {
		system("CLS");
		printf("ERROR, ATMINA NETIKA REZERVETA! PROGRAMMAS KLUDA!");
		getch();
	}

	for (i = 0; i < skaits; i++) {
		if (strcmpi(uzvards, pas[i].uzv) == 0)
		{ // Salîdzina ievadîto ar DB esoðo
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
		do { // Programma piedâvâ ievadît ID, kuru dzçst, kamçr
			// tiek ievadits atïautais ID (no ierakstiem, kurus atradâm)
			printf("IEVADIET IERAKSTA ID, KURU GRIBAT DZEST\n");
			printf("ID = ");
			scanf("%hd", &tmp2);

			for (i = 0; i < tmp; i++) // Pârbauda vai tika ievadîts pareizais ID
				if (tmp2 == id[i])
					error = 0;
				else if (i == (tmp - 1))
					printf("\nTIKA IEVADITS NEPAREIZS ID\n\n");

		}
		while (error != 0);

		for (i = (tmp2 - 1); i < (skaits - 1); i++)
		{ // Dzçðanas gadîjumâ sakârto DB
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
// Funkcija vadîtâju atlasîðanai
// ==============================================================================
void atlasisana(void) {
	int i;
	short tmp; // TMP variablis
	char uzvards[15]; // Uzvârda variablis salîdzinâðanai
	char tmps[20] = "                   ";
	// TMP variablis - ierakstu pievienoðanai

	system("CLS");
	printf("IEVADIET VADITAJA UZVARDU\n");
	printf("Uzvards = ");
	scanf("%s", &uzvards);
	strncat(uzvards, tmps, 14 - strlen(uzvards));
	printf("\n\n");

	tmp = 0;
	for (i = 0; i < skaits; i++) { // Meklç vadîtâjus ar konkrçtu uzvârdu
		if (strcmpi(uzvards, pas[i].uzv) == 0) { // Salîdzina ar DB datiem
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
// Funkcija visu auto marku vadîtâju atlasei
// ==============================================================================
void individ(void) {
	int i;
	char aut[20]; // Auto marku salîdzinâðanai
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
	{ // Tiek meklçti vadîtâji, kuri vada konkrçtas markas auto
		if (strcmpi(aut, pas[i].autoMarka) == 0)
		{ // Salîdzina ievadîtos datus ar DB
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
// Funkcija DB saglabâðanai
// ==============================================================================
void saglabasana(void) {
	int i;

	system("CLS");
	printf("DATU BAZE TIKA VEIKSMIGI SAGLABATA");
	f = fopen("db.dat", "wb");
	fwrite(&skaits, sizeof(short), 1, f);
	for (i = 0; i < skaits; i++) { // Saglabâjam failâ
		fwrite(&pas[i], sizeof(vad), 1, f);
		pas[i].id = i + 1;
	}
	fclose(f);

	getch();
}
