#include "KruskalMST.h"

using namespace std;

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
	/*
	 * TODO
	 */

	this->treeID.assign(G.getV(), -1);
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
	vector<Edge> edges = G.edges();

	// Hier werden alle Kanten von G geliefert.
	for (int i = 0; i < edges.size(); i++)
	{
		pq.push(edges[i]);
	}

	// Anfangs ist jeder Knoten ein Baum für sich. Während zusammenfügung, achtet man auf Zyklen.
	for (int i = 0; i < G.getV(); i++)
	{
		treeID[i] = i;
	}

	while(!pq.empty())
	{
		Edge edg = pq.top();
		pq.pop();

		int v = edg.either();
		int w = edg.other(v);

		if (treeID[v] != treeID[w])
		{
			mst.push_back(edg);
			int treeid_w = treeID[w];
			for (int i = 0; i < G.getV(); i++)
			{
				if (treeID[i] == treeid_w)
				{
					treeID[i] = treeID[v];
				}
			}
		}
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
vector<Edge> KruskalMST::edges() const
{
	/*
	 * TODO
	 */

	return this->mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
	/*
	 * TODO
	 */

	double sum = 0.0;
	for (int i = 0; i < mst.size(); i++)
	{
		sum += mst[i].weight();
	}

	return sum;
}
