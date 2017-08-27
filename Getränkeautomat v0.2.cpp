// Getränkeautomat v0.2.cpp : Defines the entry point for the console application.

//Es gibt mehrere Getränke zur Auswahl: Wasser, Limonade und Bier.


#include "stdafx.h"
#include "stdlib.h"
#include "Windows.h"


#if 0
#define WASSER_WAHL 0
#define Limonade_WAHL 1
#define Bier_WAHL 2
#define Cola_WAHL 3
#define Pepsi_WAHL 4
#define Exit_WAHL 10
#else	
enum 
{			
	WASSER_WAHL = 0,
	Limonade_WAHL = 1,
	Bier_WAHL = 2,
	Cola_WAHL = 3,
	Pepsi_WAHL = 4,
	Exit_WAHL = 10,
};
#endif

bool Regal[5][5] = { // 3 Typen, 5 Fächer
	{true, true,  true,  false, false}, // 0 = Wasser
	{true, true,  false, false, false}, // 1 = Limonade
	{true, false, false, true, false},  // 2 = Bier
	{true, true, true, true, false},  // 3 = Cola
	{true, false, true, false, true}  // 4 = Pepsi
};

#define ARRAY_COUNT(array_name) (sizeof(array_name)/sizeof(array_name[0]))

bool IsBottleAvailable(int Sorte)
{
	bool IsExisting = false;
	for (int i = 0; i < ARRAY_COUNT(Regal[0]); i++)
	{
		if (Regal[Sorte][i]) IsExisting = true;
	}
	return IsExisting;
}

int main()
{

	bool IsRunning = true;
	while (IsRunning)
	{
		system("cls");

		int sorte;
		printf("Waehlen Sie ihr Getraenk aus\n");
		printf("%d) Wasser (0.50 Euro)\n", WASSER_WAHL);
		printf("%d) Limonade (1.00 Euro)\n", Limonade_WAHL);
		printf("%d) Bier (2.50 Euro)\n", Bier_WAHL);
		printf("%d) Cola (2.30 Euro)\n", Cola_WAHL);
		printf("%d) Pepsi (2.20 Euro)\n", Pepsi_WAHL);
		printf("Geben Sie 1, 2 oder 3 ein: ");
		fseek(stdin, 0, SEEK_END);
		scanf_s("%d", &sorte);

		// lege den zu bezahlenden Betrag fest

		float preis = 0;
		switch (sorte)
		{
		case WASSER_WAHL: preis = 0.5; break;
		case Limonade_WAHL: preis = 1.0; break;
		case Bier_WAHL: preis = 2.0; break;
		case Cola_WAHL: preis = 2.30f; break;
		case Pepsi_WAHL: preis = 2.20f; break;
		case Exit_WAHL: IsRunning = false; continue;
		default: continue;
		}

		// prüfe Fach, ob Flasche vorhanden
		if (!IsBottleAvailable(sorte))
		{
			printf("\nKeine Flasche vorhanden!\n");
			Sleep(2500);
			continue;
		}

		// Aufforderung zur Bezahlung

		float einwurf;
		float einwurf_summe = 0;
		do
		{
			einwurf = 0;
			printf("\nBitte werfen Sie %.2f Euro ein: ", preis - einwurf_summe);
			scanf_s("%f", &einwurf);
			einwurf_summe += einwurf;  // einwurf_summe = einwurf_summe + einwurf;

			// überprüfe Geldstück

			if (einwurf_summe == preis)
			{
				printf("\nVielen Dank, bitte entnehmen Sie ihr Getraenk.\n\n");
			}
			else if (einwurf_summe < preis)
			{
				printf("\nSie haben %.2f Euro zu wenig eingeworfen.\n", preis - einwurf_summe);
				printf("\nSie muessen noch %.2f Euro einwerfen.\n", preis - einwurf_summe);
			}
			else
			{
				printf("\nSie haben %.2f Euro zu viel eingeworfen.\n", einwurf_summe - preis);
				printf("\nSie kriegen noch %.2f Euro zurueck.\n\n", einwurf_summe - preis);
			}
		} while (einwurf_summe < preis);

		// Flasche auswerfen

		for (int i = ARRAY_COUNT(Regal[0])-1; i >= 0; i--)
		{
			if (Regal[sorte][i])
			{
				Regal[sorte][i] = false;
				break;
			}
		}

		Sleep(2500);
	}

	system("pause");
    return 0;
}

