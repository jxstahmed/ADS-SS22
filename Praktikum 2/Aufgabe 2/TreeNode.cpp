/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>

////////////////////////////////////
// Ihr Code hier:
TreeNode::TreeNode(int NodeOrderID, int NodeChronologicalID, std::string Name, int Age, double Income, int PostCode)
{
	this->NodeOrderID = NodeOrderID;
	this->NodeChronologicalID = NodeChronologicalID;
	this->Name = Name;
	this->Age = Age;
	this->Income = Income;
	this->PostCode = PostCode;
}

TreeNode::TreeNode(TreeNode* copy)
{
	this->NodeOrderID = copy->NodeOrderID;
	this->NodeChronologicalID = copy->NodeChronologicalID;
	this->Name = copy->Name;
	this->Age = copy->Age;
	this->Income = copy->Income;
	this->PostCode = copy->PostCode;
}

int TreeNode::get_NodeOrderID()
{
	return this->NodeOrderID;
}

void TreeNode::set_NodeOrderID(int no)
{
	this->NodeOrderID = no;
}

int TreeNode::get_NodeChronologicalID()
{
	return this->NodeChronologicalID;
}

void TreeNode::set_NodeChronologicalID(int ncl)
{
	this->NodeChronologicalID = ncl;
}

string TreeNode::get_name()
{
	return this->Name;
}

void TreeNode::set_name(string name)
{
	this->Name = name;
}

int TreeNode::get_age()
{
	return this->Age;
}

void TreeNode::set_age(int age)
{
	this->Age = age;
}

double TreeNode::get_income()
{
	return this->Income;
}

void TreeNode::set_income(double i)
{
	this->Income = i;
}

int TreeNode::get_PostCode()
{
	return this->PostCode;
}

void TreeNode::set_PostCode(int pc)
{
	this->PostCode = pc;
}

TreeNode* TreeNode::get_left()
{
	return this->left;
}

void TreeNode::set_left(TreeNode* left)
{
	this->left = left;
}

TreeNode* TreeNode::get_right()
{
	return this->right;
}

void TreeNode::set_right(TreeNode* right)
{
	this->right = right;
}

void TreeNode::print()
{
	cout << "NodeID: " << this->get_NodeChronologicalID()
		 << ", Name: "<< this->get_name()
		 << ", Alter: "<< this->get_age()
		 << ", Einkommen: "<< this->get_income()
		 << ", PLZ: "<< this->get_PostCode()
		 << ", PosID: " << this->get_NodeOrderID() << endl;
}

void TreeNode::ausgabe()
{
	cout << std::setw(4) << this->get_NodeChronologicalID() << "|"
		<< setw(12) << this->get_name() << "|"
		<< setw(8) << this->get_age() << "|"
		<< setw(8) << this->get_income() << "|"
		<< setw(10) << this->get_PostCode() << "|"
		<< setw(9) << this->get_NodeOrderID() << "|" << endl;
}
//
////////////////////////////////////
