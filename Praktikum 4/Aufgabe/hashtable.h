#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <vector>

using namespace std;

class HashTable
{

private:	
	int strategie = 1;
	int size;						// Gr��e der HashTable
	int elements;					// Anz. d. Elemente in HashTable
	int collisionCount;				// Anz. d. Kollisionen beim Einf�gen
	double threshold_rehashing;			// Schwellwert f�rs rehashing (size/elements)
	vector<int>* hashTable;				// HashTable
	int hashValue(int item);			// calculate hash value
	void rehashing();					// rehashing

public:
	HashTable(int size, double threshold = 0.6);		// Konstruktor
	~HashTable();								// Destruktor
	int insert(int item);						// f�gt ein Element der Hashtabelle hinzu
	int at(int i);								// Liefert das i-te Element der Hashtabelle zur�ck
	int getCollisionCount();    			// Liefert die Anzahl der Kollisionen zur�ck
	int getSize();					// Liefert die Gr��e der Hashtabelle zur�ck
	int getElements();				// Liefert die Anzahl der Elemente der Hashtabelle zur�ck
	void setStrategie(int st);
	void print() const;
};

// Helper Funktion:
int get_next_prime(int x);			// Gibt zu einer natuerlichen Zahl a, die n�chstgr��ere Primzahl zur�ck

#endif 