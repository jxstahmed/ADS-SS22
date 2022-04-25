/*************************************************
* ADS Praktikum 2.1
* RingNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "RingNode.h"


// Ihr Code hier:
RingNode::RingNode()
{
	this->next = nullptr;
}

RingNode::RingNode(int oldAge, std::string description, std::string symbolicData)
{
	this->oldAge = oldAge;
	this->description = description;
	this->symbolicData = symbolicData;
	this->next = nullptr;
}

int RingNode::getAge()
{
	return this->oldAge;
}

void RingNode::setAge(int oldAge)
{
	this->oldAge = oldAge;
}

std::string RingNode::getDescription()
{
	return this->description;
}

void RingNode::setDescription(std::string description)
{
	this->description = description;
}

std::string RingNode::getData()
{
	return this->symbolicData;
}

void RingNode::setData(std::string symbolicData)
{
	this->symbolicData = symbolicData;
}

RingNode* RingNode::getNext()
{
	return this->next;
}

void RingNode::setNext(RingNode* next)
{
	this->next = next;
}


// 
////////////////////////////////////