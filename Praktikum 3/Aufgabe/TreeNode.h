/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

class TreeNode
{

private:

	///////////////////////////////////////
	// Ihr Code hier:

	int NodeOrderID;
	int NodeChronologicalID;
	std::string Name;
	int Age;
	double Income;
	int PostCode;
	bool red;

	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;

	//
	////////////////////////////////////

public:

	TreeNode(int NodeOrderID, int NodeChronologicalID, std::string Name, int Age, double Income, int PostCode);
	int getNodeOrderID();
	void setNodeOrderID(int NodeOrderID);
	int getNodeChronologicalID();
	void setNodeChronologicalID(int NodeChronologicalID);
	std::string getName();
	void setName(std::string Name);
	int getAge();
	void setAge(int Age);
	double getIncome();
	void setIncome(double Income);
	int getPostCode();
	void setPostCode(int PostCode);
	bool getRed() const;
	void setRed(bool farbe);
	TreeNode* getLeft() const;
	void setLeft(TreeNode* links);
	TreeNode* getRight() const;
	void setRight(TreeNode* rechts);
	TreeNode* getParent() const;
	void setParent(TreeNode* eltern);
	void print();
};
