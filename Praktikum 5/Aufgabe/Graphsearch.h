#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>


namespace Graphsearch
{

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in/out] count      Aktuell gearbeitet zusammenhaengende Graph
		* \psrsm[in/out] id			Zu welchem Graph ist die Knoten Zusammenhaengend
		*/
	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo,int& count, std::vector<int>& id)
	{
		/*
		 * TODO
		 */
		
		if (v != 0)
		{
			std::cout << " -> " << v;
		}
		marked[v] = true;
		id[v] = count;

		for (Edge w : G.getAdj(v))	// Für jeden Loop, speichert er das Objekt v aus der adjazensliste in w.
		{
			if (marked[w.other(v)] == false)
			{
				edgeTo[w.other(v)] = v;
				DFS_recursive(G, w.other(v), marked, edgeTo,count, id);
			}
		}
	}

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		/*
		 * TODO
		 */

		std::vector<int> id;
		id.resize(G.getV(), -1);

		int count = 0;
		edgeTo.assign(G.getV(),-1);
		marked.assign(G.getV(), false);
	
		DFS_recursive(G, v, marked, edgeTo, count, id);
		for (int i = 0; i < id.size(); i++)
		{
			if (id[i] != 0)
			{
				return false;
			}
		}

		//std::cout << std::endl;
		return true;
	}

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		/*
		 * TODO:
		 */

		std::queue<int> q;
		q.push(v);

		bool verbunden = true;
		edgeTo.assign(G.getV(), -1);
		marked.assign(G.getV(), false);

		while (!q.empty())
		{
			int x = q.front();
			q.pop();
			if (marked[x] == true)
			{
				continue;
			}

			if (x != v)
			{
				std::cout << " -> " << x;
			}

			marked[x] = true;

			for (Edge w : G[x])
{
				if (marked[w.other(x)] == false)
				{
					if (edgeTo[w.other(x)] == -1)
					{
						edgeTo[w.other(x)] = x;
					}
					q.push(w.other(x));
				}
			}
		}

		for (int i = 0; i < G.getV(); i++)
		{
			if (marked[i] == false)
			{
				verbunden = false;
				break;
			}
		}
		
		//std::cout << std::endl;
		return verbunden;
	}
}
