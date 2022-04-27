/*************************************************
 * ADS Praktikum 2.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>
#include <vector>

class Tree
{

private:
    ///////////////////////////////////////
    // Ihr Code hier:
    TreeNode* anker;
    int currentNodeChronolicalID;
    vector<TreeNode*> baum;
    //
    ////////////////////////////////////

public:
    ///////////////////////////////////////
    // Ihr Code hier:
    Tree();
    ~Tree();
    void addNode(string Name, int Age, double Income, int  PostCode);
    bool deleteNode(int NodeOrderID);
    bool searchNode(string Name);
    void printAll(void);
    TreeNode* minimum(TreeNode* min);
    bool loesche(int NodeOrderID);
    TreeNode* loeschen_rekursive(int NodeOrderId, TreeNode* knoten);
    vector<TreeNode*> vektor(string Name);
    void levelOrder(void);
    //
    ////////////////////////////////////
    // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
    // bleiben!
    friend TreeNode* get_anker(Tree& TN);
};
