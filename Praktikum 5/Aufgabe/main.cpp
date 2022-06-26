#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"

using namespace std;

int main()
{
	Catch::Session().run();

	int eingabe = 0;
	EdgeWeightedDigraph dGraph("graph1.txt");
	EdgeWeightedGraph Graph("graph1.txt");

	while (eingabe != 8)
	{

		system("PAUSE");
		system("CLS");

		cout << "==========================================================" << endl
			 << "	Praktikum 5: Graphenalgorithmen ~ by Ahmed" << endl
			 << "==========================================================" << endl;

		cout << "1) Graph Einlesen" << endl
			<< "2) Tiefensuche" << endl
			<< "3) Breitensuche" << endl
			<< "4) MST nach Prim (Eingaben: Startknoten)" << endl
			<< "5) MST nach Kruskal" << endl
			<< "6) Kurzerste Wege nach Djikstra (Eingabe: Startknoten)" << endl
			<< "7) Ausgabe der Adjazenzliste" << endl
			<< "8) Program beenden" << endl
			<< "Weiter mit beliebiger Eingabe ..." << endl
			<< "?> ";

		cin >> eingabe;
		cout << endl;
		
		// Graph Einlesen
		if (eingabe == 1)
		{
			int lesen;
			
			cout << "Bitte waehlen Sie ein Graph aus: " << endl;
			cout << "	1.Graph" << endl
				 << "	2.Graph" << endl
				 << "	3.Graph" << endl
				 << "?> ";
			cin >> lesen;

			if (lesen == 1)
			{
				dGraph = EdgeWeightedDigraph("graph1.txt");
				Graph = EdgeWeightedGraph("graph1.txt");
			}
			else if (lesen == 2)
			{
				dGraph = EdgeWeightedDigraph("graph2.txt");
				Graph = EdgeWeightedGraph("graph2.txt");
			}
			else
			{
				dGraph = EdgeWeightedDigraph("graph3.txt");
				Graph = EdgeWeightedGraph("graph3.txt");
			}
		}

		//------------------------------------------------------------------------
		// 1. Ausgabe eines Graphen als Adjazenzliste implementieren
		//------------------------------------------------------------------------
		if (eingabe == 7)
		{
			for (int i = 0; i < Graph.getV(); i++)
			{
				cout << i;

				for (Edge e : Graph[i])
				{
					cout << "  -> " << e.other(i) << " [" << e.weight() << "]";
				}
				
				cout << endl;
			}
			cout << endl;;
		}
		

		//------------------------------------------------------------------------
		// 2. Suche in Graphen
		//------------------------------------------------------------------------
		// Verwenden Sie hierfür die Vorlagen in Graphsearch.h
		//
		// Beispielaufruf der Tiefensuche: 
		// std::vector<bool> marked;
		// std::vector<int>  edgeTo;
		// bool connected = Graphsearch::DFS(G1, start, marked, edgeTo);
		if (eingabe == 2)
		{
			int start = 0;

			cout << "Tiefensuche (Depth-First-Search (DFS)) - Startknoten : 0 " << endl;

			vector<bool> marked;
			vector<int> edgeTo;

			cout << "Besuchsreihenfolge:" << endl << start;
			bool verbunden = Graphsearch::DFS(Graph, start, marked, edgeTo);
			
			cout << endl << endl << "EdgeTo_Array:" << endl;

			for (int i = 0; i < edgeTo.size(); i++)
			{
				cout << i << " -> " << edgeTo[i];
				if (i == start)
				{
					cout << " (Startknoten)";
				}
				cout << endl;
			}

			cout << endl << "Marked-Array:" << endl;
			for (int i = 0; i < marked.size(); i++)
			{
				cout << i << " -> ";
				if (marked[i])
				{
					cout << "true";
				}
				else
				{
					cout << "false";
				}

				if (i == start)
				{
					cout << " (Startknoten)";
				}
				cout << endl;
			}

			cout << endl << "Graph ist "; 

			if (!verbunden)
			{
				cout << "nicht ";
			}
			cout << "zusammenhaengend\n" << endl;
		}

		if (eingabe == 3)
		{
			int start = 0;

			cout << "\Breitensuche (Breadth-First-Search (DFS)) - Startknoten : ? ";
			cin >> start;

			vector<bool> marked;
			vector<int> edgeTo;

			cout << "Besuchsreihenfolge:" << endl << start;
			bool verbunden = Graphsearch::BFS(Graph, start, marked, edgeTo);

			cout << endl << endl << "EdgeTo_Array:" << endl;
			for (int i = 0; i < edgeTo.size(); i++)
			{
				cout << i << " -> " << edgeTo[i];
				if (i == start)
				{
					cout << " (Startknoten)";
				}
				cout << endl;
			}
			cout << endl << "Marked-Array:" << endl;
			for (int i = 0; i < marked.size(); i++)
			{
				cout << i << " -> ";

				if (marked[i])
				{
					cout << "true";
				}
				else
				{
					cout << "false";
				}

				if (i == start)
				{
					cout << " (Startknoten)";
				}
				cout << endl;
			}
			cout << endl << "Graph ist ";
			if (!verbunden)
			{
				cout << "nicht ";
			}
			cout << "zusammenhaengend" << endl << endl;
		}

		//------------------------------------------------------------------------
		// 3. Minimaler Spannbaum mit Prim und Kruskal
		//------------------------------------------------------------------------
		// Vorlage für Prim ist die Klasse PrimMST (PrimMST.h + PrimMST.cpp)
		// Vorlage für Kruskal ist die Klasse KruskalMST (KruskalMST.h + KruskalMST.cpp)
		//
		// Beispielaufruf von Prim:
		// PrimMST prim(G, 0);
		if (eingabe == 4)
		{
			int start = 0;
			cout << "Startknoten: ? ";
			cin >> start;
			cout << endl;

			cout << "Minimaler Spannbaum (MST) nach Prim: " << endl;
			PrimMST prim(Graph, start);

			cout << "Gewicht: " << prim.weight() << endl;
			cout << "Adjazenliste:" << endl;

			struct node
			{
				int w;
				int weight;
			};

			vector<vector<node>> ergebnis;
			ergebnis.resize(Graph.getV());

			for (Edge edge : prim.edges())
			{
				int v = edge.either();
				int w = edge.other(v);

				node p;
				p.w = w;
				p.weight = edge.weight();
				ergebnis[v].push_back(p);
			}

			for (int i = 0; i < ergebnis.size(); i++)
			{
				if (ergebnis[i].empty())
				{
					continue;
				}

				cout << i;
				for (int j = 0; j < ergebnis[i].size(); j++)
				{
					cout << " -> " << ergebnis[i][j].w << " [" << ergebnis[i][j].weight << "]";
				}
				cout << endl;
			}
			cout << endl;
		}
		if (eingabe == 5)
		{
			cout << "Minimaler Spannbaum (MST) nach Kruskal: " << endl;
			KruskalMST kruskal(Graph);

			cout << "Gewicht: " << kruskal.weight() << endl;
			cout << "Adjazenliste:" << endl;

			struct node
			{
				int w;
				int weight;
			};

			vector<vector<node>> ergebnis;
			ergebnis.resize(Graph.getV());

			for (Edge edge : kruskal.edges())
			{
				int v = edge.either();
				int w = edge.other(v);

				node p;
				p.w = w;
				p.weight = edge.weight();
				ergebnis[v].push_back(p);
			}
			for (int i = 0; i < ergebnis.size(); i++)
			{
				if (ergebnis[i].empty())
				{
					continue;
				}

				cout << i;
				for (int j = 0; j < ergebnis[i].size(); j++)
				{
					cout << " -> " << ergebnis[i][j].w << " [" << ergebnis[i][j].weight << "]";
				}
				cout << endl;
			}
			cout << endl;
		}


		//------------------------------------------------------------------------
		// 4. Kuerzeste Wege mit Dijkstra
		//------------------------------------------------------------------------
		// Beispielaufruf von Dijkstra
		//
		// EdgeWeightedDigraph G1_directed("graph1.txt");
		// Dijkstra dijkstra(G1_directed, start);
		// path = dijkstra.pathTo(target);
		if (eingabe == 6)
		{
			int start = 0;
			int ziel = 6;
			cout << "Startknoten: ? ";
			cin >> start;

			cout << "Zielknoten: ? ";
			cin >> ziel;

			DijkstraSP dijkstra(dGraph, start);
			vector<DirectedEdge> path = dijkstra.pathTo(ziel);


			cout << endl << "Gewichtete Kanten des Graphen: ";
			for (int i = 0; i < dGraph.getV(); i++)
			{
				cout << endl << i;

				for (DirectedEdge e : dGraph[i])
				{
					cout << "  -> " << e.to() << " [" << e.weight() << "]";
				}
			}

			cout << endl << "Kurzerster Weg (Djikstra):" << endl
				 << "Start:  " << start << endl
				 << "Ziel:   " << ziel << endl
				 << "Pfad:   " << start;

			for (DirectedEdge p : path)
			{
				cout << " [" << p.weight() << "] -> " << p.to();
			}
			cout << endl << "Kosten: " << dijkstra.distTo(ziel) << endl << endl;
		}


		//------------------------------------------------------------------------
		// 5. Menü für Benutzereingaben
		//------------------------------------------------------------------------
		// Alle Funktionalitäten aus der Aufgabenstellung muessen umgesetzt werden
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("CLS");
		}
	}


	return 0;
}


/*
Laufzeiten:

 - Dijkstra:	O(|E| + |V| log |V|)

 - KruskalMST:	O(E log E)

 - PrimMST:		Adjazenjsmatrix = O(v²) | Heap/Liste = O(V log V + E log V)



 Speicheraufwand:

  - Edges:				2 + 2 * E			(2)

  - Knoten:				2 + |V| + |E|		(3)

  - Adjazenzmatrix:		|V|²				(1)

  - Adjazenzliste:		|V| + |E|			(4)



  Ablauf:

  - Dijkstra:		Kürzester Weg von einem Start zum Endknoten. Besucht und Gewicht Update über wege.

  - KruskalMST:		MST vom Startknoten und wählt immer den günstigsten Pfad im Graph.

  - Prim:			MST vom Startknoten und nimmt den günstigsten Pfad zu einem Knoten. | Ohne Zyklen

*/