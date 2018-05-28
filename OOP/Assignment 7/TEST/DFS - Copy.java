import java.util.*;

// depth-first visit assuming a WHITE starting vertex. dfsList
// contains the visited vertices in reverse order of finishing time.
// when checkForCycle is true, the function throws an exception if
// it detects a cycle
//C++ TO JAVA CONVERTER TODO TASK: Java has no concept of a 'friend' function:
//ORIGINAL LINE: friend void dfsVisit(graph<T>& g, const T& sVertex, LinkedList<T>& dfsList, boolean checkForCycle)
private void dfsVisit(graph<T> g, T sVertex, LinkedList<T> dfsList, boolean checkForCycle)
{
	// indices for vertex positions in vInfo
	int pos_sVertex;
	int pos_neighbor;

	// iterator to scan the adjacency set of a vertex
	Iterator<neighbor> adj;

	// alias to simplify access to the vector vInfo
	ArrayList<vertexInfo<T>> vlist = g.vInfo;

	// fetch the index for sVertex in vInfo; throw an exception
	// if the starting vertex is not in the graph
	pos_sVertex = g.getvInfoIndex(sVertex);

	if (pos_sVertex == -1)
	{
		throw graphError("graph dfsVisit(): vertex not in the graph");
	}

	// color vertex GRAY to note its discovery
	vlist.get(pos_sVertex).color = vertexInfo<T>.GRAY;

	// create an alias for the adjacency set of sVertex
	TreeSet<neighbor> edgeSet = vlist.get(pos_sVertex).edges;

	// sequence through the adjacency set and look for vertices
	// that are not yet discovered (colored WHITE). recursively call
	// dfsVisit() for each such vertex. if a vertex in the adjacency
	// set is GRAY, the vertex was discovered during a previous
	// call and there is a cycle that begins and ends at the
	// vertex; if checkForCycle is true, throw an exception
	for (adj = edgeSet.iterator(); adj.hasNext();)
	{
		pos_neighbor = (adj.next()).dest;
		if (vlist.get(pos_neighbor).color == vertexInfo<T>.WHITE)
		{
			dfsVisit(g, (*(g.vInfo[pos_neighbor].vtxMapLoc)).first, dfsList, checkForCycle);
		}
		else if (vlist.get(pos_neighbor).color == vertexInfo<T>.GRAY && checkForCycle)
		{
			throw graphError("graph dfsVisit(): graph has a cycle");
		}
	}

	// finished with vertex sVertex. make it BLACK and add it to
	// the front of dfsList
	vlist.get(pos_sVertex).color = vertexInfo<T>.BLACK;
	dfsList.addFirst((*(g.vInfo[pos_sVertex].vtxMapLoc)).first);
}

import java.util.*;

// depth-first search. dfsList contains all the graph vertices in the
// reverse order of their finishing times
//C++ TO JAVA CONVERTER TODO TASK: Java has no concept of a 'friend' function:
//ORIGINAL LINE: friend void dfs(graph<T>& g, LinkedList<T>& dfsList)
private void dfs(graph<T> g, LinkedList<T> dfsList)
{
	int i;

	// clear dfsList
//C++ TO JAVA CONVERTER TODO TASK: There is no direct equivalent to the STL list 'erase' method in Java:
	dfsList.erase(dfsList.iterator(), dfsList.end());

	// initialize all vertices to WHITE
	for (i = 0;i < g.vInfo.size(); i++)
	{
		if (g.vInfo[i].occupied)
		{
			g.vInfo[i].color = vertexInfo<T>.WHITE;
		}
	}

	// scan vInfo, calling () dfsVisit() for each WHITE vertex.
	for (i = 0;i < g.vInfo.size(); i++)
	{
		if (g.vInfo[i].occupied && g.vInfo[i].color == vertexInfo<T>.WHITE)
		{
			dfsVisit(g,(*(g.vInfo[i].vtxMapLoc)).first, dfsList, false);
		}
	}
}