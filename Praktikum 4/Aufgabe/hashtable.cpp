#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size, double threshold) 
{
	collisionCount = elements = 0;
	hashTable = new vector<int>;
	hashTable->resize(size, -1);
	this->size = size;
	this->threshold_rehashing = threshold;
}

HashTable::~HashTable()
{
	delete hashTable;
}

void HashTable::setStrategie(int strategie)
{
	this->strategie = strategie;
}

// Berechnung des Hashwertes mit quadr. Sondieren
int HashTable::hashValue(int item) 
{
	int strategie = this->strategie;

	int i = 0;
	int x = item % size;

	if (strategie == 0)
	{
		// Lineares Sondieren
		while (hashTable->at(((x + i) % size)) != -1)
		{
			++i;
			++collisionCount;
		}
		return ((x + i) % size);
	}
	else if (strategie == 1)
	{
		// Quadratisches Sondieren
		while (hashTable->at(((item % size + i * i) % size)) != -1)
		{
			++i;
			++collisionCount;
		}
		return ((x + i * i) % size);
	}
	else
	{
		// Doppeltes Hashing
		int prim = get_next_prime(0);
		for (int b = 0; b < size; b++)
		{
			if (get_next_prime(prim) > size)
			{
				break;
			}
			prim = get_next_prime(prim);
		}
		while (hashTable->at((x + i * (prim - x % prim)) % size) != -1)
		{
			++i;
			++collisionCount;
		}

		return ((x + i * (prim - x % prim)) % size);
	}
}
	
bool primzahlen(int z)
{
	int x, i;
	int prim[168] = { 0 };
	int zaehler = 0;
	for (x = 2; x <= 1000; x++)
	{
		for (i = 2; i <= x; i++)
		{
			if (x % i == 0 && x != i)
			{
				break;
			}
			if (i == x)
			{
				prim[zaehler] = i;
				zaehler++;
			}
		}
	}

	for (int i = 0; i < 168; i++)
	{
		if (z = prim[i])
		{
			return true;
		}
	}
	return false;
}

void HashTable::rehashing()
{
	double voll = (double)this->elements / (double)this->size;
	if (this->threshold_rehashing <= voll)
	{
		int newSize = 0;
		int neusize = (2 * getSize()) + 1;
		if (primzahlen(neusize))
		{
			newSize = neusize;
		}
		else
		{
			newSize = get_next_prime((2 * getSize()) + 1);
		}

		if (newSize <= 997)
		{
			int hashIndex = 0, item = 0;
			HashTable* H = new HashTable(newSize);

			for (int i = 0; i < this->getSize(); i++)
			{
				if (hashTable->at(i) == -1)
				{
					continue;
				}
				else
				{
					item = this->hashTable->at(i);
					hashIndex = H->hashValue(item);
					H->hashTable->at(hashIndex) = item;
					H->elements++;
				}
			}

			delete this->hashTable;
			this->hashTable =  H->hashTable;
			this->size = H->size;
			this->elements = H->elements;
			this->collisionCount = H->collisionCount;
			this->threshold_rehashing = H->threshold_rehashing;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

int HashTable::insert(int item) 
{
	int hashVal = hashValue(item);
	hashTable->at(hashVal) = item;
	++elements;
	this->rehashing();

	return 0;
}

int HashTable::at(int i) 
{
	return hashTable->at(i);
}

int HashTable::getCollisionCount() 
{
	return this->collisionCount;
}

int HashTable::getSize() 
{
	return this->size;
}

int HashTable::getElements() 
{
	return this->elements;
}

void HashTable::print() const
{
	cout << "HashTable->size(): "
		 << size << endl;
	for (int i = 0; i < size; i++)
	{
		cout << i << ": " << hashTable->at(i) << endl;
	}
}

int get_next_prime(int x)
{
	x = x + 1;
	bool found = true;
	while (true)
	{
		found = true;
		for (int i = 2; i <= sqrt(x); i++)
		{
			if (x % i == 0)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return x;
		}
		x += 1;
	}
}