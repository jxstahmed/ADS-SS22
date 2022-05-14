/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>

class Tree
{

private:

	int currentNodeChronologicalID;
	TreeNode* anker;

	void balance(TreeNode* knoten);
	bool split4Node(TreeNode* knoten);
	int proofRBCriterion(TreeNode* knoten);
	bool rotateTreeRight(TreeNode* eltern, TreeNode* kind);
	bool rotateTreeLeft(TreeNode* eltern, TreeNode* kind);
	int getNiveau(TreeNode* knoten);

public:
	///////////////////////////////////////
	// Ihr Code hier:
	Tree();
	~Tree();
	bool addNode(std::string name, int age, double income, int postcode);
	bool searchNode(std::string suchen);
	void printAll();
	void preorder(TreeNode* suchen, std::string name, bool& ergebnis);
	void printpreorder(TreeNode* knoten);
	void printLevel();
	void printLevelOrder(void);
	void printLevelOrder(int niveau);
	void start(TreeNode* knoten);
	//
	////////////////////////////////////
	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
	// bleiben!
	friend TreeNode* get_anker(Tree& TN);
};
