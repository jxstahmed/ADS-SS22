/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.h"

using namespace std;


int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:

	int eingabe = 0;
	string beschreibung;
	string daten;

	Ring neu;

	while (eingabe != 4)
	{
		cout << "========================================" << endl;
		cout << "SuperBackUp-Organizer over 9000, by. Son Goku" << endl;
		cout << "========================================" << endl;

		cout << "1) Backup anlegen" << endl;
		cout << "2) Backup suchen" << endl;
		cout << "3) Alle Backups ausgeben" << endl;
		cout << "4) Um das Programm zu beenden" << endl;

		cout << "?> ";
		cin >> eingabe;
		cout << endl;

		switch (eingabe)
		{
			case 1:
				cout << "+Neuen Datensatz anlegen" << endl;
				cout << "Beschreibung ?> ";
				cin >> beschreibung;
				cout << "Daten ?> ";
				cin >> daten;
				cout << endl;

				neu.addNode(beschreibung, daten);
				break;

			case 2:
				cout << "+Nach welchen Daten soll gesucht werden?" << endl;
				cout << "?> ";
				cin >> daten;

				neu.search(daten);
				cout << endl;
				break;

			case 3:
				neu.print();
				cout << endl;
				break;
		}
	}

	//
	///////////////////////////////////////
	system("Pause");
	return 0;
}
