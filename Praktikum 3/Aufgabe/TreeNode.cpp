/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

////////////////////////////////////
// Ihr Code hier:
TreeNode::TreeNode(int NodeOrderID, int NodeChronologicalID, string Name, int Age, double Income, int PostCode)
{
	this->NodeOrderID = NodeOrderID;
	this->NodeChronologicalID = NodeChronologicalID;
	this->Name = Name;
	this->Age = Age;
	this->Income = Income;
	this->PostCode = PostCode;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	this->setRed(true);
}

int TreeNode::getNodeOrderID()
{
	return NodeOrderID;
}

void TreeNode::setNodeOrderID(int NodeOrderID)
{
	this->NodeOrderID;
}

int TreeNode::getNodeChronologicalID()
{
	return NodeChronologicalID;
}

void TreeNode::setNodeChronologicalID(int NodeChronologicalID)
{
	this->NodeChronologicalID = NodeChronologicalID;
}

std::string TreeNode::getName()
{
	return Name;
}

void TreeNode::setName(std::string Name)
{
	this->Name = Name;
}

int TreeNode::getAge()
{
	return Age;
}

void TreeNode::setAge(int Age)
{
	this->Age = Age;
}

double TreeNode::getIncome()
{
	return Income;
}
void TreeNode::setIncome(double Income)
{
	this->Income = Income;
}

int TreeNode::getPostCode()
{
	return PostCode;
}

void TreeNode::setPostCode(int PostCode)
{
	this->PostCode = PostCode;
}

bool TreeNode::getRed() const
{
	return red;
}

void TreeNode::setRed(bool farbe)
{
	red = farbe;
}
TreeNode* TreeNode::getLeft() const
{
	return left;
}

void TreeNode::setLeft(TreeNode* links)
{
	left = links;
}
TreeNode* TreeNode::getRight() const
{
	return right;
}
void TreeNode::setRight(TreeNode* rechts)
{
	right = rechts;
}

TreeNode* TreeNode::getParent() const
{
	return parent;
}

void TreeNode::setParent(TreeNode* eltern)
{
	parent = eltern;
}

void TreeNode::print()
{
	cout << setw(4) << this->getNodeChronologicalID() << " | "
		<< setw(20) << this->getName() << " |"
		<< setw(4) << this->getAge() << " |"
		<< setw(8) << this->getIncome() << " |"
		<< setw(10) << this->getPostCode() << " |"
		<< setw(9) << this->getNodeOrderID() << " |"
		<< setw(3) << this->getRed() << endl;
}
//
////////////////////////////////////
