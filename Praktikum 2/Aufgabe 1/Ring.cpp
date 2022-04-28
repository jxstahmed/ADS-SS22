/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

// Ihr Code hier:

Ring::Ring()
{
	anker = nullptr;
	this->countNodes = 0;
}

void Ring::addNode(std::string description, std::string symbolicData)
{
	RingNode* neu = new RingNode(0, description, symbolicData);

	if (countNodes == 0)
	{
		anker = neu;
		anker->setNext(neu);
		countNodes++;
	}
	else if (countNodes == 6)
	{
		RingNode* loeschen = anker->getNext();
		neu->setNext(anker->getNext()->getNext());
		anker->setNext(neu);
		anker = neu;
		delete loeschen;

		RingNode* ptr = neu->getNext();

		for (int i = 1; i < countNodes; i++)
		{
			ptr->setAge(ptr->getAge()+1);
			ptr = ptr->getNext();
		}

	}
	else
	{
		neu->setNext(anker->getNext());
		anker->setNext(neu);
		anker = neu;
		countNodes++;

		RingNode* ptr = neu->getNext();

		for (int i = 1; i < countNodes; i++)
		{
			ptr->setAge(ptr->getAge() + 1);
			ptr = ptr->getNext();
		}
	}

}

bool Ring::search(std::string symbolicData)
{
	if (anker != nullptr)
	{
		RingNode* ptr = anker->getNext();

		for (int i = 0; i < countNodes; i++)
		{
			if (ptr->getData() == symbolicData)
			{
				std::cout << "Gefunden in Backup: Alter " << ptr->getAge() << ", Beschreibung: " << ptr->getDescription() << ", Daten : " << ptr->getData() << std::endl;
				return true;
			}
			ptr = ptr->getNext();
		}
	}

	std::cout << "Datensatz konnte nicht gefunden werden." << std::endl;
	return false;
}

void Ring::print()
{
	RingNode* ptr = anker;

	std::cout << "Alter: " << ptr->getAge() << ", Beschreibung: " << ptr->getDescription() << ", Daten: " << ptr->getData() << std::endl;
	std::cout << "--------------------------" << std::endl;

	RingNode* ptr2 = anker;
	int zaehler = 0;

	while (zaehler < countNodes - 1)
	{
		ptr2 = ptr2->getNext();

		if (ptr2->getNext() == ptr)
		{
			std::cout << "Alter: " << ptr2->getAge() << ", Beschreibung: " << ptr2->getDescription() << ", Daten: " << ptr2->getData() << std::endl;
			std::cout << "--------------------------" << std::endl;

			ptr = ptr2;
			zaehler++;
		}
	}
}
//
////////////////////////////////////
