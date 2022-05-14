/*************************************************
 * ADS Praktikum 2.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

////////////////////////////////////
// Ihr Code hier:

Tree::Tree()
{
	anker = nullptr;
	currentNodeChronologicalID = 0;
}

Tree::~Tree()
{

}

bool Tree::addNode(string name, int age, double income, int postcode)
{
	int NodeOrderID = age + (int)income + postcode;

	TreeNode* neu = new TreeNode(NodeOrderID, currentNodeChronologicalID, name, age, income, postcode);
	neu->setRed(true);

	TreeNode* eltern = nullptr;
	TreeNode* ptr = anker;

	while (ptr != nullptr)
	{
		split4Node(ptr); // Überprüfen ob hier split benötigt wird.
		eltern = ptr; // Zeiger auf Eltern, damit das später angepasst wird.


		if (neu->getNodeOrderID() < ptr->getNodeOrderID())
		{
			ptr = ptr->getLeft();
		}
		else
		{
			ptr = ptr->getRight();
		}
	}
	if (eltern == nullptr)		// Liste ist Leer.
	{
		anker = neu;
		neu->setRed(false);
		neu->setParent(nullptr);
		this->currentNodeChronologicalID++;
	}
	else if (neu->getNodeOrderID() < eltern->getNodeOrderID())	//Neuer Knoten kleiner als Eltern Knoten
	{
		eltern->setLeft(neu);
		neu->setParent(eltern);
		this->currentNodeChronologicalID++;
	}
	else		//Neuer Knoten größer als Eltern Knoten
	{
		eltern->setRight(neu);
		neu->setParent(eltern);
		this->currentNodeChronologicalID++;
	}

	TreeNode* suchen = neu;
	int roteknoten = 0;
	while (suchen != nullptr) // Falls 2 rote Knoten  hintereinander gefunden werden, muss balanciert werden.
	{

		if (!suchen->getRed())
		{
			roteknoten = 0;
		}
		else
		{
			roteknoten++;
		}
		if (roteknoten == 2)
		{
			balance(suchen);
		}
		suchen = suchen->getParent();
	}
	return true;
}

void Tree::preorder(TreeNode* suchen, string name, bool& ergebnis)		// Suche in Preorder
{
	if (suchen != nullptr)	// Der Baum ist nicht Leer.
	{
		if (suchen->getName() == name)	// Erster Knoten ist direkt der richtige.
		{
			ergebnis = true;

			cout << "+ Fundstellen." << endl;
			cout << "ID: " << suchen->getNodeChronologicalID()
				<< ", Name:  " << name
				<< ", Age:  " << suchen->getAge()
				<< ", Income:  " << suchen->getIncome()
				<< ", PostCode:  " << suchen->getPostCode()
				<< ", Order:  " << suchen->getNodeOrderID()
				<< ", Red: " << suchen->getRed() << endl << endl;

		}
		if (suchen->getLeft() != nullptr)	// Rekursiv links suchen
		{
			preorder(suchen->getLeft(), name, ergebnis);
		}

		if (suchen->getRight() != nullptr)	// Rekursiv rechts suchen
		{
			preorder(suchen->getRight(), name, ergebnis);
		}
	}
}

bool Tree::searchNode(string name)
{
	TreeNode* suchen = anker;
	bool ergebnis = false;

	if (anker == nullptr)	// Wenn der Baum leer ist.
	{
		return ergebnis;
	}

	preorder(suchen, name, ergebnis);	// Rekursive Suche.

	return ergebnis;
}


void Tree::printpreorder(TreeNode* knoten)
{
	if (knoten != nullptr)	// Wenn der Baum leer ist
	{
		knoten->print();

		printpreorder(knoten->getLeft());
		printpreorder(knoten->getRight());
	}
}

void Tree::printAll()
{
	cout << "ID  | Name                  | Age | Income  | PostCode  | OrderID  | Red " << endl;
	cout << "----+-----------------------+-----+---------+-----------+----------+----" << endl;
	printpreorder(anker);
	cout << endl;

}

void Tree::printLevel()
{
	cout << "ID   | Name                 | Age    | Income  | PostCode  | OrderID  | Red " << endl;
	cout << "-----+----------------------+--------+---------+-----------+----------+----" << endl;

	if (anker == nullptr)
	{
		cout << "Der Baum ist leer.";
		return;
	}
	else
	{
		TreeNode* ausgabe = anker;
		std::queue<TreeNode*> aktuell;

		aktuell.push(ausgabe);

		while (!aktuell.empty()) {

			ausgabe = aktuell.front();
			aktuell.pop();

			ausgabe->print();

			if (ausgabe->getLeft() != nullptr)
			{
				aktuell.push(ausgabe->getLeft());
			}

			if (ausgabe->getRight() != nullptr)
			{
				aktuell.push(ausgabe->getRight());
			}
		}
	}
}

bool Tree::split4Node(TreeNode* knoten)
{
	if (knoten->getRed())	//Wenn der Knoten rot ist
	{
		return false;
	}
	if (knoten->getLeft() != nullptr && knoten->getRight() != nullptr)	//Es existieren zwei Nachfolger Knoten
	{

		if (knoten->getLeft()->getRed() && knoten->getRight()->getRed())	//Wenn beide Nachfolger rot sind
		{

			if (anker != knoten)	// Nur wenn der Knoten nicht der Anker ist
			{
				knoten->setRed(true);
			}

			// Umfärben der Nachfolger 
			knoten->getLeft()->setRed(false);
			knoten->getRight()->setRed(false);
			return true;
		}
	}
	return false;
}

bool Tree::rotateTreeRight(TreeNode* eltern, TreeNode* kind)
{
	if (anker == eltern)	// Wenn wir uns am Anker befinden
	{
		anker = kind;
		kind->setParent(nullptr);
	}
	else
	{
		TreeNode* großeltern = eltern->getParent();
		if (großeltern->getNodeOrderID() > kind->getNodeOrderID())
		{
			großeltern->setLeft(kind);
			kind->setParent(großeltern);
		}
		else
		{
			großeltern->setRight(kind);
			kind->setParent(großeltern);
		}
	}

	eltern->setParent(kind);
	eltern->setLeft(kind->getRight());

	if (eltern->getLeft() != nullptr)
	{
		eltern->getLeft()->setParent(eltern);
	}
	kind->setRight(eltern);

	return true;
}

bool Tree::rotateTreeLeft(TreeNode* eltern, TreeNode* kind)
{
	if (eltern == anker)	// Wenn wir uns am Anker befinden
	{
		anker = kind;
		kind->setParent(nullptr);
	}
	else
	{
		TreeNode* großeltern = eltern->getParent();
		if (großeltern->getNodeOrderID() > kind->getNodeOrderID())
		{
			großeltern->setLeft(kind);
			kind->setParent(großeltern);
		}
		else
		{
			großeltern->setRight(kind);
			kind->setParent(großeltern);
		}
	}
	eltern->setParent(kind);
	eltern->setRight(kind->getLeft());

	if (eltern->getRight() != nullptr)
	{
		eltern->getRight()->setParent(eltern);
	}
	kind->setLeft(eltern);
	return true;
}

void Tree::balance(TreeNode* knoten)
{
	//Links-Rechts-Knick -> Links-Rechts-Rotation
	if (knoten->getParent() != nullptr && knoten->getRight() != nullptr)
	{
		if (knoten->getNodeOrderID() < knoten->getParent()->getNodeOrderID() && knoten->getRight()->getRed())
		{
			rotateTreeLeft(knoten, knoten->getRight());
			rotateTreeRight(knoten->getParent()->getParent(), knoten->getParent());
			knoten->getParent()->setRed(false);
			knoten->getParent()->getRight()->setRed(true);

			return;
		}
	}

	//Rechts-Links-Knick -> Rechts-Links-Rotation
	if (knoten->getParent() != nullptr && knoten->getLeft() != nullptr)
	{
		if (knoten->getNodeOrderID() > knoten->getParent()->getNodeOrderID() && knoten->getLeft()->getRed())
		{
			rotateTreeRight(knoten, knoten->getLeft());
			rotateTreeLeft(knoten->getParent()->getParent(), knoten->getParent());
			knoten->getParent()->setRed(false);
			knoten->getParent()->getLeft()->setRed(true);

			return;
		}
	}

	// Rotation ohne Knick -> Rechts
	if (knoten->getParent() != nullptr && knoten->getRight() != nullptr)
	{
		if (knoten->getNodeOrderID() > knoten->getParent()->getNodeOrderID() && knoten->getRight()->getRed())
		{
			rotateTreeLeft(knoten->getParent(), knoten);
			knoten->setRed(false);
			knoten->getLeft()->setRed(true);

			return;
		}
	}

	// Rotation ohne Knick -> Links
	if (knoten->getParent() != nullptr && knoten->getLeft() != nullptr)
	{
		if (knoten->getNodeOrderID() < knoten->getParent()->getNodeOrderID() && knoten->getLeft()->getRed())
		{
			rotateTreeRight(knoten->getParent(), knoten);
			knoten->setRed(false);
			knoten->getRight()->setRed(true);

			return;
		}
	}
}

int Tree::getNiveau(TreeNode* knoten)
{
	int niveau = 0;

	while (knoten->getParent() != nullptr)
	{
		if (knoten->getParent() != nullptr)
		{
			niveau++;
		}

		knoten = knoten->getParent();
	}
	return niveau;
}

void Tree::printLevelOrder(int niveau)
{
	queue<TreeNode*> knoten;
	queue<int> niveauq;

	TreeNode* ptr = anker;
	int niv = -1;
	int nivalt = -2;

	if (ptr == nullptr)
	{
		cout << "Der Baum ist Leer." << endl;
		return;
	}
	else
	{
		knoten.push(ptr);
		niveauq.push(niv + 1);

		cout << endl;
		cout << "Niv.  " << niveau << ":";

		while (!niveauq.empty())
		{
			ptr = knoten.front();
			knoten.pop();

			niv = niveauq.front();
			niveauq.pop();

			if (ptr->getLeft() != nullptr)
			{
				if (!ptr->getLeft()->getRed())		//Der Linke Nachfolger ist Schwarz
				{
					knoten.push(ptr->getLeft());
					niveauq.push(niv + 1);
					if (niveau == niv)
					{
						cout << "(";
					}
				}
				else
				{
					if (ptr->getLeft()->getLeft() != nullptr)
					{

						knoten.push(ptr->getLeft()->getLeft());
						niveauq.push(niv + 1);
					}

					if (ptr->getLeft()->getRight() != nullptr)
					{

						knoten.push(ptr->getLeft()->getRight());
						niveauq.push(niv + 1);
					}

					if (niveau == niv)
					{
						cout << "(" << ptr->getLeft()->getNodeOrderID() << ", ";
					}
				}
			}
			else
			{
				if (niveau == niv)
				{
					cout << "(";
				}
			}

			if (niveau == niv)
			{
				cout << ptr->getNodeOrderID();
			}

			if (ptr->getRight() != nullptr)
			{
				if (!ptr->getRight()->getRed())		//Der Rechte Nachfolger ist schwarz
				{
					knoten.push(ptr->getRight());
					niveauq.push(niv + 1);
					if (niveau == niv)
					{
						cout << ") ";
					}
				}
				else
				{
					if (ptr->getRight()->getLeft() != nullptr)
					{
						knoten.push(ptr->getRight()->getLeft());
						niveauq.push(niv + 1);
					}

					if (ptr->getRight()->getRight() != nullptr)
					{
						knoten.push(ptr->getRight()->getRight());
						niveauq.push(niv + 1);
					}

					if (niveau == niv)
					{
						cout << ", " << ptr->getRight()->getNodeOrderID() << ") ";
					}
				}
			}
			else
			{
				if (niveau == niv)
				{
					cout << ") ";
				}
			}

			if (niveau < niv)
			{
				break;
			}
		}
	}
	cout << endl << endl;
}

void Tree::printLevelOrder()
{
	queue<TreeNode*> knoten;
	queue<int> niveau;

	TreeNode* ptr = anker;
	int niv = -1;
	int altniv = -2;

	if (ptr == nullptr)
	{
		cout << "Der Baum ist Leer." << endl;
		return;
	}
	else
	{
		knoten.push(ptr);
		niveau.push(niv + 1);

		while (!knoten.empty())
		{

			ptr = knoten.front();
			knoten.pop();

			niv = niveau.front();
			niveau.pop();

			if (altniv != niv)
			{
				cout << endl;
				cout << "Niv. " << niv << ": ";
				altniv = niv;
			}

			if (ptr->getLeft() != nullptr)
			{

				if (!ptr->getLeft()->getRed())	//Der Linke Nachfolger ist Schwarz
				{
					knoten.push(ptr->getLeft());
					niveau.push(niv + 1);
					cout << "(";
				}
				else
				{
					if (ptr->getLeft()->getLeft() != nullptr)
					{
						knoten.push(ptr->getLeft()->getLeft());
						niveau.push(niv + 1);
					}

					if (ptr->getLeft()->getRight() != nullptr)
					{
						knoten.push(ptr->getLeft()->getRight());
						niveau.push(niv + 1);
					}
					cout << "(" << ptr->getLeft()->getNodeOrderID() << ", ";
				}
			}
			else
			{
				cout << "(";
			}
			cout << ptr->getNodeOrderID();

			if (ptr->getRight() != nullptr)
			{

				if (!ptr->getRight()->getRed())		//Der Rechte Nachfolger ist schwarz
				{
					knoten.push(ptr->getRight());
					niveau.push(niv + 1);

					cout << ") ";
				}
				else
				{
					if (ptr->getRight()->getLeft() != nullptr)
					{
						knoten.push(ptr->getRight()->getLeft());
						niveau.push(niv + 1);
					}

					if (ptr->getRight()->getRight() != nullptr)
					{
						knoten.push(ptr->getRight()->getRight());
						niveau.push(niv + 1);
					}
					cout << ", " << ptr->getRight()->getNodeOrderID() << ") ";
				}
			}
			else
			{
				cout << ") ";
			}
		}
		cout << endl << endl;
	}
}

void Tree::start(TreeNode* knoten)
{
	int hoehe = proofRBCriterion(knoten);

	if (hoehe == -1)
	{
		cout << "Der Baum ist nicht Schwarzausgeglichen!" << endl;
	}
	else
	{
		cout << "Der Baum hat eine Schwarzausgeglichenheit. Hoehe ist: " << hoehe << endl;
	}
}

int Tree::proofRBCriterion(TreeNode* knoten)
{
	int links_hoehe = 0;
	int rechts_hoehe = 0;

	if (knoten == nullptr)	// Wenn der Baum Leer ist
	{
		return -1;
	}
	else
	{
		if (knoten->getLeft() == nullptr && knoten->getRight() == nullptr)	//Es handelt sich um einen Blattknoten -> Höhe 0
		{
			return 0;
		}
		if (knoten->getLeft() != nullptr)		// Nur Links Nachfolger -> Höhe Links [Rekursiv Links]
		{
			links_hoehe = proofRBCriterion(knoten->getLeft());
		}
		if (knoten->getRight() != 0)		// Nur Rechts Nachfolger -> Höhe Rechts [Rekursiv Rechts]
		{
			rechts_hoehe = proofRBCriterion(knoten->getRight());
		}

		if (knoten->getLeft() != nullptr && knoten->getRight() != nullptr)  // Es existieren 2 Nachfolger
		{
			if (knoten->getLeft()->getRed() && knoten->getRight()->getRed())	// Beide Nachfolger sind Rot
			{
				if (links_hoehe == rechts_hoehe)
				{
					return links_hoehe;
				}
				else
				{
					return -1;
				}
			}

			if (knoten->getLeft()->getRed() && !knoten->getRight()->getRed())	//Links ist Rot und Rechts ist Schwarz
			{
				if (links_hoehe == rechts_hoehe + 1)
				{
					return links_hoehe;
				}
				else
				{
					return -1;
				}
			}

			if (!knoten->getLeft()->getRed() && knoten->getRight()->getRed())	//Links ist Schwarz und Rechts ist Rot
			{
				if (links_hoehe + 1 == rechts_hoehe)
				{
					return rechts_hoehe;
				}
				else
				{
					return -1;
				}
			}

			if (!knoten->getLeft()->getRed() && !knoten->getRight()->getRed())		//Wenn beide Nachfolger schwarz sind
			{
				if (links_hoehe == rechts_hoehe)
				{
					return links_hoehe + 1;
				}
				else
				{
					return -1;
				}
			}
		}
	}
}