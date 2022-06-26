#include <assert.h>
#include "DijkstraSP.h"

using namespace std;

/**
 * Füge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verläuft und deren
 * Ziel w dem Startknoten s am nächsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	/*
	 * TODO
	 */

	for (DirectedEdge edge : G[v])
	{
		int w = edge.to();
		if (distToVect[w] > distToVect[v] + edge.weight())
		{
			distToVect[w] = distToVect[v] + edge.weight();
			edgeTo[w] = edge;

			if (pq.contains(w))
			{
				pq.change(w, distToVect[w]);
			}
			else
			{
				pq.push(w, distToVect[w]);
			}
		}
	}
}

/**
 * Fuert den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	/*
	 * TODO
	 */

	distToVect.assign(G.getV(), -1);

	for (int v = 0; v < G.getV(); v++)
	{
		distToVect[v] = DBL_MAX; // Wir wählen den größten wer der von Double aufgenommen werden kann, um bei günstigeren Wegen zu aktualisieren.
	}

	distToVect[s] = 0.0;
	pq.push(s, 0.0);

	while (!pq.empty())
	{
		int minknoten = pq.top().value;
		pq.pop();
		relax(G, minknoten);
	}
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v) const
{
	/*
	 * TODO
	 */

	return distToVect[v];
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
	/*
	 * TODO
	 */

	return distToVect[v] != -1;
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
vector<DirectedEdge> DijkstraSP::pathTo(int v) 
{
	/*
	 * TODO
	 */

	vector<DirectedEdge> weg;
	int ptr = v;

	while (distToVect[ptr] > 0.0)
	{
		weg.push_back(edgeTo[ptr]);
		ptr = edgeTo[ptr].from();
	}

	int size = weg.size();
	for (int i = 0; i < size/2; i++)
	{
		DirectedEdge temp = weg[i];
		weg[i] = weg[size - i - 1];
		weg[size - i - 1] = temp;
	}
	return weg;
}
