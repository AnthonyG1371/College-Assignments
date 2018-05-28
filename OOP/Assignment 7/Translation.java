// maintains vertex properties, including its set of
// neighbors
template <typename T>
class vertexInfo
----public class vertexInfo<T>
{
	public:
		// used by graph algorithms
		enum vertexColor { WHITE, GRAY, BLACK };

		// iterator pointing at a pair<T,int> object in the vertex map
		typename map<T,int>::iterator vtxMapLoc;											-----

		// set of adjacent (neighbor) objects for the current vertex
		set<neighbor> edges;

		/// maintains the in-degree of the vertex
		int inDegree;

		// indicates whether the object currently represents a vertex
		bool occupied;
		boolean occupied;
		
		// indicate if a vertex is marked in an algorithm that traverses
		// the vertices of a graph
		vertexColor color;

		// available to algorithms for storing relevant data values
		int dataValue;

		// available to graph algorithms; holds parent which is
		// a vertex that has an edge terminating in the current vertex
		int parent;

		// default constructor
		vertexInfo(): inDegree(0), occupied(true)
		{}

		// constructor with iterator pointing to the vertex in the map
		vertexInfo(typename map<T,int>::iterator iter):
				vtxMapLoc(iter), inDegree(0), occupied(true)
		{}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// uses vtxMap to obtain the index of v in vInfo
template <typename T>
int graph<T>::getvInfoIndex(const T& v) const
---public int (final E v) extends graph
public int 
{
	// iter used in map lookup
	typename vertexMap::const_iterator iter;
	// index that is returned
	int pos;

	// find the map entry with key v
	iter = vtxMap.find(v);

	// make sure v is in the map
	if (iter == vtxMap.end())
		pos = -1;
	else
		// the index into vInfo is the value of the map entry
		pos = (*iter).second;

	return pos;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// perform the breadth-first traversal from sVertex and
// return the set of visited vertices
friend set<T> bfs(graph<T>& g, const T& sVertex)
---public static <E> bfs(graph<E> g, final T sVertex)
{
	// BFS uses a queue to store indices of adjacent vertices from vInfo
   queue<int> visitQueue;
   ---queue<Integer> visitQueue = new LinkedList();
   
	// set of vertices in BFS
	set<T> visitSet;
    ----set<E> visitSet;
	
	// use to store indices in vInfo
	int currVertex, neighborVertex;

	// use to search edge sets for unvisited vertices
	set<neighbor>::iterator adj;
    ----Iterator adj = neighbor.iterator();
	int i;

	// find the index of the starting vertex
	currVertex = g.getvInfoIndex(sVertex);
    ----currVertex = g.getvInfoIndex(sVertex);

	// check for a nonexistent starting vertex
	if (currVertex == -1)
		throw graphError("graph bfs(): vertex not in the graph");

	// initialize all vertices in the graph to unvisited (WHITE)
	for (i=0;i < g.vInfo.size(); i++)
		if (g.vInfo[i].occupied)
			g.vInfo[i].color = vertexInfo<T>::WHITE;
		    ----g.vInfo[i].color = WHITE;

   visitQueue.push(currVertex);   // initialize the queue
   
   while (!visitQueue.empty())
   {
      // remove a vertex from the queue
      currVertex = visitQueue.front();
		visitQueue.pop();
		// indicate that the vertex has been visited
		g.vInfo[currVertex].color = vertexInfo<T>::BLACK;
		---g.vInfo[currVertex].color = BLACK;
		
		// put the vertex in visitSet
		visitSet.insert((*(g.vInfo[currVertex].vtxMapLoc)).first);

		// create an alias for the edge set of currVertex
		set<neighbor>& edgeSet = g.vInfo[currVertex].edges;
		// sequence through the edge set and look for vertices
		// that have not been visited
		for (adj = edgeSet.begin(); adj != edgeSet.end(); adj++)
		{
			neighborVertex = (*adj).dest;

			if (g.vInfo[neighborVertex].color == vertexInfo<T>::WHITE)
			if (g.vInfo[neighborVertex].color == WHITE)
			{
				g.vInfo[neighborVertex].color = vertexInfo<T>::GRAY;
				g.vInfo[neighborVertex].color = GRAY;
				visitQueue.push(neighborVertex);
			}
		}
   }

	return visitSet;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// this algorithm is a private friend of the graph class
private:

// depth-first visit assuming a WHITE starting vertex. dfsList
// contains the visited vertices in reverse order of finishing time.
// when checkForCycle is true, the function throws an exception if
// it detects a cycle
friend void dfsVisit(graph<T>& g, const T& sVertex, list<T>& dfsList,
							bool checkForCycle)
{
	// indices for vertex positions in vInfo
	int pos_sVertex, pos_neighbor;

	// iterator to scan the adjacency set of a vertex
	set<neighbor>::iterator adj;

	// alias to simplify access to the vector vInfo
	vector<vertexInfo<T> >& vlist = g.vInfo;

	// fetch the index for sVertex in vInfo; throw an exception
	// if the starting vertex is not in the graph
	pos_sVertex = g.getvInfoIndex(sVertex);

	if (pos_sVertex == -1)
		throw graphError("graph dfsVisit(): vertex not in the graph");

	// color vertex GRAY to note its discovery
	vlist[pos_sVertex].color = vertexInfo<T>::GRAY;

	// create an alias for the adjacency set of sVertex
	set<neighbor>& edgeSet = vlist[pos_sVertex].edges;

	// sequence through the adjacency set and look for vertices
	// that are not yet discovered (colored WHITE). recursively call
	// dfsVisit() for each such vertex. if a vertex in the adjacency
	// set is GRAY, the vertex was discovered during a previous
	// call and there is a cycle that begins and ends at the
	// vertex; if checkForCycle is true, throw an exception
	for (adj = edgeSet.begin(); adj != edgeSet.end(); adj++)
	{
		pos_neighbor = (*adj).dest;
		if (vlist[pos_neighbor].color == vertexInfo<T>::WHITE)
		if (vlist[pos_neighbor].color == WHITE)
			dfsVisit(g,(*(g.vInfo[pos_neighbor].vtxMapLoc)).first,
							 dfsList, checkForCycle);
		else if (vlist[pos_neighbor].color == vertexInfo<T>::GRAY
					&& checkForCycle)
		else if (vlist[pos_neighbor].color == GRAY
					&& checkForCycle)
			throw graphError("graph dfsVisit(): graph has a cycle");
	}

	// finished with vertex sVertex. make it BLACK and add it to
	// the front of dfsList
	vlist[pos_sVertex].color = vertexInfo<T>::BLACK;
	dfsList.push_front((*(g.vInfo[pos_sVertex].vtxMapLoc)).first);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// return to the public section for the remaining algorithms
public:

// depth-first search. dfsList contains all the graph vertices in the
// reverse order of their finishing times
friend void dfs(graph<T>& g, list<T>& dfsList)
---public void dfs(graph<E> g, list<E> dfsList)
{
	int i;

	// clear dfsList
	dfsList.erase(dfsList.begin(), dfsList.end());

	// initialize all vertices to WHITE
	for (i=0;i < g.vInfo.size(); i++)
		if (g.vInfo[i].occupied)
			g.vInfo[i].color = vertexInfo<T>::WHITE;

	// scan vInfo, calling () dfsVisit() for each WHITE vertex.
	for (i=0;i < g.vInfo.size(); i++)
		if (g.vInfo[i].occupied && g.vInfo[i].color ==
											vertexInfo<T>::WHITE)
			dfsVisit(g,(*(g.vInfo[i].vtxMapLoc)).first, dfsList, false);
}

---
public static void main(string args[])
{
}