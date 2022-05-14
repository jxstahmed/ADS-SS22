#define CATCH_CONFIG_RUNNER
#include "Tree.h"
#include "catch.h"
#include <iostream>
#include <string>

using namespace std;

void mainscreen_addTreeCSV(Tree*& ref)
{
	char j;
	cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
		"importieren(j / n) ? >";
	cin >> j;
	if (j == 'j')
	{
		ifstream csvread;
		csvread.open("ExportZielanalyse.csv", ios::in);
		if (!csvread.is_open())
			cerr << "Fehler beim Lesen!" << endl;
		else
		{
			string name, age, postcode, income;

			while (!csvread.eof())
			{
				getline(csvread, name, ';');
				getline(csvread, age, ';');
				getline(csvread, income, ';');
				getline(csvread, postcode, '\n');
				ref->addNode(name, stoi(age), stod(income), stoi(postcode));
			}
			csvread.close();
		}
		cout << "+ Daten wurden dem Baum hinzugefuegt." << endl << endl;
	}
}

int main()
{
	int result = Catch::Session().run();

	Tree* baum = new Tree;

	int eingabe = 0;
	string name = "";
	int alter = 0;
	double einkommen = 0.0;
	int plz = 0;
	int orderID = 0;
	int niveau = 0;

	while (eingabe != 7)
	{
		cout << "=============================" << endl; // Beispiel: Menu der Anwendung
		cout << "       Made by Ahmed" << endl;
		cout << "=============================" << endl;
		cout << "1) Datensatz einfuegen, manuell" << endl;
		cout << "2) Datensatz einfuegen, CSV Datei" << endl;
		cout << "3) Suchen" << endl;
		cout << "4) Ausgabe in Preorder" << endl;
		cout << "5) Ausgabe in Levelorder" << endl;
		cout << "6) Ausgabe in Levelorder(mit Niveauauswahl)" << endl;
		cout << "7) Beenden" << endl;

		cout << "?> ";
		cin >> eingabe;
		cin.ignore();
		cin.clear();

		switch (eingabe)
		{
		case 1:

			cout << "+ Bitte geben Sie den Datensatz ein" << endl;
			cout << "Name ?> ";
			getline(cin, name);
			cout << "Alter ?> ";
			cin >> alter;
			cout << "Einkommen ?> ";
			cin >> einkommen;
			cout << "PLZ ?> ";
			cin >> plz;
			cout << endl;
			baum->addNode(name, alter, einkommen, plz);
			cout << "+ Ihr Datensatz wurde eingefugt" << endl << endl;

			break;

		case 2:

			mainscreen_addTreeCSV(baum);

			break;

		case 3:

			cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
			cout << "Name ?> ";
			getline(cin, name);
			cout << endl;
			baum->searchNode(name);

			break;

		case 4:

			baum->printAll();

			break;

		case 5:

			cout << "Ausgabe in Levelorder als binaerer Suchbaum: " << endl << endl;
			baum->printLevel();
			cout << endl;
			cout << "Ausgabe in Levelorder als 234-Baum: " << endl;
			baum->printLevelOrder();

			break;

		case 6:

			cout << "Bitte geben Sie das Niveau ein" << endl << "?> ";
			cin >> niveau;
			cout << endl;
			baum->printLevelOrder(niveau);

			break;

		default:

			cout << "Deine Eingabe war ungueltig!" << endl;
			break;

		}
	}

	system("pause");
	return 0;
}