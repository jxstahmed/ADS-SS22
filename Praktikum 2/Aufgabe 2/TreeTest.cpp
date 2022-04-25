/*************************************************
 * ADS Praktikum 2.1
 * Unit-Testdatei
 * Stand: 05.03.2019
 *
 *************************************************
 * Änderungen untersagt!
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include "catch.h"
#include <iostream>
#include <string>

using namespace std;

// Friend-Methode fuer Testroutine
TreeNode* get_anker(Tree& Tr)
{
    return Tr.anker;
}

/***********************************************
 * Testroutine des Baums:
 *  - Einfaches Hinzufuegen und Suchen
 *  - Loeschen in unterscheidlicher Ausprägung
 *  + Loeschen ohne Nachfolger
 *  + Loeschen mit einem Nachfolger
 *  + Loeschen mit zwei Nachfolger
 *  + Loeschen der Wurzel
 *  - Hinzufuegen vieler Nodes als Grossbaum
 */
TEST_CASE("Tree Testing", "[TREE]")
{

    Tree* nTree = new Tree();

    SECTION("Hinzufuegen von Nodes und Suche - simple")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        REQUIRE(nTree->searchNode("Mayer") == true);
        REQUIRE(nTree->searchNode("Mayer7") == true);
        REQUIRE(nTree->searchNode("Mayer6") == true);
        REQUIRE(nTree->searchNode("Mayer5") == true);
        REQUIRE(nTree->searchNode("Mayer4") == true);
        REQUIRE(nTree->searchNode("Mayer3") == true);
        REQUIRE(nTree->searchNode("Mayer2") == true);

        REQUIRE(nTree->searchNode("Mueller") == false);
        REQUIRE(nTree->searchNode("Mayer99") == false);
    }

    SECTION("Loeschen von Nodes - ohne Nachfolger")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        nTree->addNode("Mayer8", 8, 0, 0);
        REQUIRE(nTree->searchNode("Mayer8") == true);

        TreeNode* tnanker = get_anker(*nTree);

        nTree->deleteNode(8);
        REQUIRE(tnanker->get_left()->get_left() == nullptr);
    }

    SECTION("Loeschen von Nodes - mit einem Nachfolger")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        nTree->addNode("Mayer8", 8, 0, 0);
        nTree->addNode("Mayer9", 7, 0, 0);

        REQUIRE(nTree->searchNode("Mayer8") == true);
        REQUIRE(nTree->searchNode("Mayer9") == true);

        TreeNode* tnanker = get_anker(*nTree);

        // linke Seite
        nTree->deleteNode(8);
        REQUIRE(tnanker->get_left()->get_left() != nullptr);
        REQUIRE(tnanker->get_left()->get_right() == nullptr);
        REQUIRE(tnanker->get_left()->get_left()->get_NodeOrderID() == 7);

        nTree->deleteNode(7);
        REQUIRE(tnanker->get_left()->get_left() == nullptr);
        REQUIRE(tnanker->get_left()->get_right() == nullptr);
        REQUIRE(tnanker->get_left()->get_NodeOrderID() == 10);

        REQUIRE(nTree->searchNode("Mayer8") == false);
        REQUIRE(nTree->searchNode("Mayer9") == false);

        // rechte Seite
        nTree->addNode("Mayer8", 8, 0, 0);
        nTree->addNode("Mayer9", 9, 0, 0);
        REQUIRE(nTree->searchNode("Mayer8") == true);
        REQUIRE(nTree->searchNode("Mayer9") == true);

        nTree->deleteNode(8);
        REQUIRE(tnanker->get_left()->get_left() != nullptr);
        REQUIRE(tnanker->get_left()->get_left()->get_NodeOrderID() == 9);

        nTree->deleteNode(9);
        REQUIRE(tnanker->get_left()->get_left() == nullptr);
        REQUIRE(tnanker->get_left()->get_NodeOrderID() == 10);

        REQUIRE(nTree->searchNode("Mayer8") == false);
        REQUIRE(nTree->searchNode("Mayer9") == false);
    }

    SECTION("Loeschen von Nodes - mit zwei Nachfolger")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        TreeNode* tnanker = get_anker(*nTree);

        REQUIRE(tnanker->get_NodeOrderID() == 20);
        REQUIRE(tnanker->get_right()->get_NodeOrderID() == 30);
        REQUIRE(tnanker->get_right()->get_left()->get_NodeOrderID() == 25);
        REQUIRE(tnanker->get_right()->get_left()->get_right()->get_NodeOrderID() ==
                26);
        REQUIRE(tnanker->get_right()->get_right()->get_left()->get_NodeOrderID() ==
                35);

        nTree->deleteNode(30);
        REQUIRE(tnanker->get_NodeOrderID() == 20);
        REQUIRE(tnanker->get_right()->get_NodeOrderID() == 35);
        REQUIRE(tnanker->get_right()->get_right()->get_NodeOrderID() == 40);
        REQUIRE(tnanker->get_right()->get_right()->get_left() == nullptr);
        REQUIRE(tnanker->get_right()->get_right()->get_right() == nullptr);
        REQUIRE(tnanker->get_right()->get_left()->get_NodeOrderID() == 25);
        REQUIRE(tnanker->get_right()->get_left()->get_right()->get_NodeOrderID() ==
                26);
        REQUIRE(tnanker->get_right()->get_left()->get_left() == nullptr);

        nTree->deleteNode(35);
        REQUIRE(tnanker->get_NodeOrderID() == 20);
        REQUIRE(tnanker->get_right()->get_NodeOrderID() == 40);
        REQUIRE(tnanker->get_right()->get_left()->get_NodeOrderID() == 25);
    }

    SECTION("Loeschen von Nodes - ab Wurzel")
    {

        nTree->addNode("Mayer", 20, 0, 0);
        nTree->addNode("Mayer2", 10, 0, 0);
        nTree->addNode("Mayer3", 30, 0, 0);
        nTree->addNode("Mayer4", 40, 0, 0);
        nTree->addNode("Mayer5", 35, 0, 0);
        nTree->addNode("Mayer6", 25, 0, 0);
        nTree->addNode("Mayer7", 26, 0, 0);

        TreeNode* tnanker = get_anker(*nTree); // Initiale Übergrabe des Ankers

        /*
        Lösche den Baum schrittweise durch entfernen der Wurzel
        */
        REQUIRE(tnanker->get_NodeOrderID() == 20);
        nTree->deleteNode(20);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->get_NodeOrderID() == 25);
        REQUIRE(tnanker->get_right()->get_NodeOrderID() == 30);
        REQUIRE(tnanker->get_right()->get_left()->get_NodeOrderID() == 26);
        REQUIRE(tnanker->get_right()->get_right()->get_NodeOrderID() == 40);

        nTree->deleteNode(25);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->get_NodeOrderID() == 26);
        REQUIRE(tnanker->get_right()->get_NodeOrderID() == 30);
        REQUIRE(tnanker->get_right()->get_left() == nullptr);
        REQUIRE(tnanker->get_right()->get_right()->get_NodeOrderID() == 40);

        nTree->deleteNode(26);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->get_NodeOrderID() == 30);
        REQUIRE(tnanker->get_right()->get_NodeOrderID() == 40);
        REQUIRE(tnanker->get_right()->get_left()->get_NodeOrderID() == 35);
        REQUIRE(tnanker->get_right()->get_right() == nullptr);

        nTree->deleteNode(30);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->get_NodeOrderID() == 35);
        REQUIRE(tnanker->get_right()->get_NodeOrderID() == 40);
        REQUIRE(tnanker->get_right()->get_left() == nullptr);
        REQUIRE(tnanker->get_right()->get_right() == nullptr);

        nTree->deleteNode(35);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->get_NodeOrderID() == 40);
        REQUIRE(tnanker->get_right() == nullptr);
        REQUIRE(tnanker->get_left()->get_NodeOrderID() == 10);

        nTree->deleteNode(40);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker->get_NodeOrderID() == 10);
        REQUIRE(tnanker->get_right() == nullptr);
        REQUIRE(tnanker->get_left() == nullptr);

        nTree->deleteNode(10);
        tnanker = get_anker(
            *nTree); // Anker hat sich geändert, neue Übergabe erfoderlich

        REQUIRE(tnanker == nullptr);
    }

    SECTION("Hinzufuegen von Nodes - Erzeuge Grossbaum")
    {

        for (int i = 0; i < 124; i++)
        {
            string info = "Name-" + to_string(i);

            // Random Income und PostCode
            double r   = rand() + 1;
            int    PostCode = rand() + 1;
            nTree->addNode(info, 0, r, PostCode);
        }
        nTree->printAll();
        nTree->levelOrder();
        std::cout << "========================================" << endl;
        std::cout << "Testausgabe des Grossbaums abgeschlossen" << endl;
    }
}

/***********************************************
 * Testroutine des Knotens:
 *  - Einfaches pruefen der Getter und Setter in Ausführung
 */
TEST_CASE("TreeNode Testing", "[TREENODE]")
{

    Tree* smallTree = new Tree();
    smallTree->addNode("Herzog", 20, 0, 0);
    TreeNode* ref = get_anker(*smallTree);

    SECTION("Getter von TreeNode - simple")
    {

        REQUIRE(ref->get_name() == "Herzog");
        REQUIRE(ref->get_age() == 20);
        REQUIRE(ref->get_income() == 0);
        REQUIRE(ref->get_left() == nullptr);
        REQUIRE(ref->get_right() == nullptr);
        REQUIRE(ref->get_NodeChronologicalID() == 0);
        REQUIRE(ref->get_NodeOrderID() == 20);
        REQUIRE(ref->get_PostCode() == 0);
    }

    SECTION("Setter von TreeNode - simple")
    {

        ref->set_age(22);
        REQUIRE(ref->get_age() == 22);

        ref->set_income(1000);
        REQUIRE(ref->get_income() == 1000);

        ref->set_left(nullptr);
        REQUIRE(ref->get_left() == nullptr);

        ref->set_right(nullptr);
        REQUIRE(ref->get_right() == nullptr);

        ref->set_name("Kaiser");
        REQUIRE(ref->get_name() == "Kaiser");

        ref->set_PostCode(1000);
        REQUIRE(ref->get_PostCode() == 1000);
    }
    delete smallTree;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// http://www.hashemall.com/
// Zeile 1-291 hat den SHA 256 Hashwert:
// F87C64B1D8F66C7C18FB2EF4B3696AD49A939784186E7E3824749CFA707C1620
