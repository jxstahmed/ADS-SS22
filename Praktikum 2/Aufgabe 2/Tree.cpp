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
		if (anker->get_NodeOrderID() < neu->get_NodeOrderID()) // Wenn der neue größer ist als der Anker, dann nach rechts.
		{
			kind = eltern->get_right();
		}
		else	// Wenn der neue kleiner ist als der Anker, dann nach links.
		{
			kind = eltern->get_left();
		}

		while (kind != nullptr)	//Durch traversieren um den Knoten richtig einzusezten. Solange wir kein nullptr erreichen.
		{

			eltern = kind;

			if (kind->get_NodeOrderID() < neu->get_NodeOrderID())
			{

				kind = kind->get_right();
			}
			else
			{
				kind = kind->get_left();
			}
		}

		if (eltern->get_NodeOrderID() < neu->get_NodeOrderID())
		{
			eltern->set_right(neu);
		}
		else
		{
			eltern->set_left(neu);
		}
	}

	baum.push_back(neu);
	currentNodeChronolicalID++;
}

bool Tree::deleteNode(int NodeOrderId)
{

	if (anker == nullptr) // Baum ist wiedermal Leer.
	{
		return false;
	}
	else
	{
		loesche(NodeOrderId);
		anker = loeschen_rekursive(NodeOrderId, anker);
	}

	currentNodeChronolicalID--;
	return true;
}

TreeNode* Tree::loeschen_rekursive(int NodeOrderID, TreeNode* anker)
{
	if (anker == nullptr)	//Baum ist Leer.
	{
		return anker;
	}
	else if (anker->get_NodeOrderID() < NodeOrderID)
	{
		anker->set_left(loeschen_rekursive(NodeOrderID, anker->get_right()));
	}
	else if (anker->get_NodeOrderID() > NodeOrderID)
	{
		anker->set_left(loeschen_rekursive(NodeOrderID, anker->get_left()));
	}
	else
	{
		if (anker->get_left() == nullptr)	// Hat nur einen rechten Nachfolger
		{
			TreeNode* neu;

			neu = anker->get_right();
			delete anker;

			return neu;

		}
		else if (anker->get_right() == nullptr)	// Hat nur einen linken Nachfolger
		{
			TreeNode* neu;

			neu = anker->get_left();
			delete anker;

			return neu;

		}
		else if (anker->get_right() != nullptr && anker->get_left() != nullptr)
		{
			TreeNode* neu;

			neu = this->minimum(anker->get_right());

			anker->set_NodeOrderID(neu->get_NodeOrderID());
			anker->set_right(loeschen_rekursive(neu->get_NodeOrderID(), anker->get_right()));
		}
	}

	return anker;
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

	auto suche = get_vektor(Name);

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


void Tree::setze_zeiger(TreeNode* y, int index)
{
	baum[index] = y;
}

vector<TreeNode*> Tree::get_vektor(string Name)	// Hier suchen wir einen Vektor [einen Knoten] dessen Name, mit dem übergebenen Namen einstimmt.
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
		cout << "Der Baum ist leer." << endl;
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
			<< setw(12) << stand->get_name() << "|"
			<< setw(8) << stand->get_age() << "|"
			<< setw(8) << stand->get_income() << "|"
			<< setw(10) << stand->get_PostCode() << "|"
			<< setw(9) << stand->get_NodeOrderID() << "|"
			<< setw(5) << aktuell << endl;

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