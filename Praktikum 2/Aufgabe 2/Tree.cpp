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
	currentNodeChronolicalID = 0;
}

Tree::~Tree()
{
	if (anker == nullptr)
	{
		return;
	}
	while (anker != nullptr)
	{
		TreeNode* loeschen = anker;

		if (anker->get_left() == nullptr && anker->get_right() == nullptr)
		{
			break;
		}

		while (true)
		{
			if (loeschen->get_left() != nullptr)
			{
				loeschen = loeschen->get_left();
			}
			else if (loeschen->get_right() != nullptr)
			{
				loeschen = loeschen->get_right();
			}
			else if (loeschen->get_left() == nullptr && loeschen->get_right() == nullptr)
			{
				delete loeschen;
				break;
			}
		}
	}
	delete anker;
}

void Tree::addNode(string Name, int Age, double Income, int  PostCode)
{
	int NodeOrderID = Age + Income + PostCode;

	TreeNode* neu = new TreeNode(NodeOrderID, currentNodeChronolicalID, Name, Age, Income, PostCode);

	TreeNode* eltern = anker;
	TreeNode* kind;

	if (anker == nullptr) // Wenn der Baum Leer ist.
	{
		anker = neu;
	}
	else {
		if (anker->get_NodeOrderID() > neu->get_NodeOrderID()) // Wenn der neue kleiner ist als der Anker, dann nach links.
		{
			kind = eltern->get_left();
		}
		else	// Wenn der neue größer ist als der Anker, dann nach rechts.
		{
			kind = eltern->get_right();
		}

		while (kind != nullptr)	//Durch traversieren um den Knoten richtig einzusezten. Solange wir kein nullptr erreichen.
		{

			eltern = kind;

			if (kind->get_NodeOrderID() > neu->get_NodeOrderID())
			{

				kind = kind->get_left();
			}
			else
			{
				kind = kind->get_right();
			}
		}

		if (eltern->get_NodeOrderID() > neu->get_NodeOrderID())
		{
			eltern->set_left(neu);
		}
		else
		{
			eltern->set_right(neu);
		}
	}

	baum.push_back(neu);
	currentNodeChronolicalID++;
}

bool Tree::deleteNode(int NodeOrderId)
{
	loesche(NodeOrderId);
	
	TreeNode* suchen = anker;
	TreeNode* eltern = nullptr;

	while (suchen != nullptr && suchen->get_NodeOrderID() != NodeOrderId)
	{
		eltern = suchen;
		if (suchen->get_NodeOrderID() > NodeOrderId)
		{
			suchen = suchen->get_left();
		}
		else
		{
			suchen = suchen->get_right();
		}
	}

	if (suchen == nullptr) // Der zu suchende Knoten wurde nicht gefunden.
	{
		return false;
	}


	if (suchen->get_left() == nullptr && suchen->get_right() == nullptr)	// Der Knoten hat keine Nachfolger. Kann einfach gelöscht werden.
	{
		if (eltern == nullptr)
		{
			anker = nullptr;
		}
		else
		{
			if (eltern->get_left() == suchen)
			{
				eltern->set_left(nullptr);
			}
			else
			{
				eltern->set_right(nullptr);
			}
		}
		delete suchen;
		currentNodeChronolicalID--;
		return true;
	}

	else if (!(suchen->get_left() != nullptr && suchen->get_right() != nullptr))	// Knoten hat nur einen Nachfolger.
	{
		TreeNode* neu;

		if (suchen->get_left() != nullptr)
		{
			neu = suchen->get_left();	// Zeiger auf Kindknoten von suchen
		}
		else
		{
			neu = suchen->get_right();	// Zeiger auf Kindknoten von suchen
		}

		if (eltern == nullptr)
		{
			anker = neu;	// Wenn Elternknoten von Suchen NULL, dann zeigt anker auf Kind knoten von Suchen
		}
		else
		{
			if (eltern->get_left() == suchen)
			{
				eltern->set_left(neu);	// Elternknoten von Suchen, bekommt Kindknoten von suchen.
			}
			else
			{
				eltern->set_right(neu);	// Elternknoten von Suchen, bekommt Kindknoten von suchen.
			}
		}
		delete suchen;
		currentNodeChronolicalID--;
		return true;
	}
	else	//Knoten hat 2 Nachfolger
	{
		TreeNode* elternmin, *min;
		elternmin = suchen;
		min = suchen->get_right();

		while (min->get_left() != nullptr)
		{
			elternmin = min;
			min = min->get_left();
		}
		
		min->set_left(suchen->get_left());
		if (elternmin != suchen)
		{
			elternmin->set_left(min->get_right());
			min->set_right(suchen->get_right());
		}
		if (eltern == nullptr)
		{
			anker = min;
		}
		else
		{
			if (eltern->get_left() == suchen)
			{
				eltern->set_left(min);
			}
			else
			{
				eltern->set_right(min);
			}
		}
		delete suchen;
		currentNodeChronolicalID--;
		return true;
	}
}
bool Tree::loesche(int NodeOrderID)
{

	for (auto anfang = baum.begin(); anfang != baum.end();)
	{

		if ((*anfang)->get_NodeOrderID() == NodeOrderID)
		{
			baum.erase(anfang);
			return true;
		}
		else
		{
			++anfang;
		}
	}

	return false;
}

bool Tree::searchNode(string Name)
{

	auto suche = vektor(Name);

	if(suche.size() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Tree::printAll(void)
{

	vector<TreeNode*> ausgabe = baum;

	while (!ausgabe.empty())
	{
		auto aktuell = ausgabe.begin();
		(*aktuell)->ausgabe();
		ausgabe.erase(ausgabe.begin());
	}
}

TreeNode* Tree::minimum(TreeNode* min)
{
	while (min->get_left() != nullptr)
	{
		min = min->get_left();
	}

	return min;
}


vector<TreeNode*> Tree::vektor(string Name)	// Hier suchen wir einen Vektor [einen Knoten] dessen Name, mit dem übergebenen Namen einstimmt.
{

	vector<TreeNode*> suchen;

	for (unsigned int i = 0; i < baum.size(); i++)
	{
		if (baum[i]->get_name() == Name)
		{
			suchen.push_back(baum[i]);
		}
	}
	return suchen;
}

void Tree::levelOrder(void)
{

	TreeNode* wurzel = anker;

	queue<TreeNode*> ausgabe;
	queue<int> level;

	if (wurzel == nullptr)
	{
		return;
	}

	ausgabe.push(wurzel);
	level.push(0);

	int vorher = -1;
	int aktuell;
	while (!ausgabe.empty())
	{
		TreeNode* stand = ausgabe.front();
		ausgabe.pop();
		aktuell = level.front();
		level.pop();

		if (vorher != aktuell)
		{
			vorher = aktuell;
		}

		cout << std::setw(4) << stand->get_NodeChronologicalID() << "|"
			<< setw(20) << stand->get_name() << "|"
			<< setw(8) << stand->get_age() << "|"
			<< setw(8) << stand->get_income() << "|"
			<< setw(10) << stand->get_PostCode() << "|"
			<< setw(9) << stand->get_NodeOrderID() << "|"
			<< setw(5) << aktuell << "|" << endl;

		if (stand->get_left() != nullptr)
		{
			ausgabe.push(stand->get_left());
			level.push(aktuell + 1);
		}
		if (stand->get_right() != nullptr)
		{
			ausgabe.push(stand->get_right());
			level.push(aktuell + 1);
		}

	}
	return;
}
//
////////////////////////////////////