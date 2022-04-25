/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode{
	
private:
	// Ihr Code hier:
	RingNode* next;
	int oldAge = 0;
	std::string description = "";
	std::string symbolicData = "";

	//	
public:
	// Ihr Code hier:
	RingNode();
	RingNode(int oldAge, std::string description, std::string symbolicData);
	int getAge();
	void setAge(int oldAge);
	std::string getDescription();
	void setDescription(std::string description);
	std::string getData();
	void setData(std::string symbolicData);
	RingNode* getNext();
	void setNext(RingNode* next);

	//
};
