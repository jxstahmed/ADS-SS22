/*************************************************
 * ADS Praktikum 2.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

using namespace std;

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
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    //
    ////////////////////////////////////

public:
    ///////////////////////////////////////
    // Ihr Code hier:
    TreeNode(int NodeOrderID, int NodeChronologicalID, std::string name, int Age, double Income, int PostCode);
    TreeNode(TreeNode* copy);

    int get_NodeOrderID();
    void set_NodeOrderID(int no);
    int get_NodeChronologicalID();
    void set_NodeChronologicalID(int ncl);
    string get_name();
    void set_name(string name);
    int get_age();
    void set_age(int age);
    double get_income();
    void set_income(double i);
    int get_PostCode();
    void set_PostCode(int pc);
    TreeNode* get_left();
    void set_left(TreeNode* left);
    TreeNode* get_right();
    void set_right(TreeNode* right);

    void print();
    void ausgabe();
    //
    ////////////////////////////////////
};
