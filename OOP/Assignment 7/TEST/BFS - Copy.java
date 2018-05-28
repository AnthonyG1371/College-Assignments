import java.util.*;

// perform the breadth-first traversal from sVertex and
// return the set of visited vertices
//C++ TO JAVA CONVERTER TODO TASK: Java has no concept of a 'friend' function:
//ORIGINAL LINE: friend TreeSet<T> bfs(graph<T>& g, const T& sVertex)
private TreeSet<T> bfs(graph<T> g, T sVertex)
{
	// BFS uses a queue to store indices of adjacent vertices from vInfo
   LinkedList<Integer> visitQueue = new LinkedList<Integer>();

	// set of vertices in BFS
	TreeSet<T> visitSet = new TreeSet<T>();

	// use to store indices in vInfo
	int currVertex;
	int neighborVertex;

	// use to search edge sets for unvisited vertices
	Iterator<neighbor> adj;
	int i;

	// find the index of the starting vertex
	currVertex = g.getvInfoIndex(sVertex);

	// check for a nonexistent starting vertex
	if (currVertex == -1)
	{
		throw graphError("graph bfs(): vertex not in the graph");
	}

	// initialize all vertices in the graph to unvisited (WHITE)
	for (i = 0;i < g.vInfo.size(); i++)
	{
		if (g.vInfo[i].occupied)
		{
			g.vInfo[i].color = vertexInfo<T>.WHITE;
		}
	}

   visitQueue.offer(currVertex); // initialize the queue

   while (!visitQueue.isEmpty())
   {
	  // remove a vertex from the queue
	  currVertex = visitQueue.peek();
		visitQueue.poll();
		// indicate that the vertex has been visited
		g.vInfo[currVertex].color = vertexInfo<T>.BLACK;

		// put the vertex in visitSet
		visitSet.add((*(g.vInfo[currVertex].vtxMapLoc)).first);

		// create an alias for the edge set of currVertex
		TreeSet<neighbor> edgeSet = g.vInfo[currVertex].edges;
		// sequence through the edge set and look for vertices
		// that have not been visited
		for (adj = edgeSet.iterator(); adj.hasNext();)
		{
			neighborVertex = (adj.next()).dest;

			if (g.vInfo[neighborVertex].color == vertexInfo<T>.WHITE)
			{
				g.vInfo[neighborVertex].color = vertexInfo<T>.GRAY;
				visitQueue.offer(neighborVertex);
			}
		}
   }

	return visitSet;
}
