//*******************************************************************
// NOTE: please read the 'More Info' tab to the right for shortcuts.
//*******************************************************************

import java.util.*;
import java.lang.Math; // headers MUST be above the first class

// one class needs to have a main() method
public class TEST
{
  // arguments are passed using the text field below this editor
  public static void main(String[] args)
  {
  }
}

public class graph<T>
{
	  public static class const_iterator extends Iterator< T, Integer >
	  {
			public const_iterator()
			{
			}

				// converts a map iterator to a graph iterator
			public const_iterator(Iterator<T,Integer> i)
			{
					typename Iterator< T, Integer > this = i;
			}

				// return the vertex pointed to by the iterator
				
			//This might pose a problem due to lack of operator overloading
			public T indirection ()
			{
			   Iterator<T,Integer> p = this;

    		   return p.first;
			}
	  }



		// constructor. initialize numVertices and numEdges to 0
		public graph()
		{
			this.numVertices = 0;
			this.numEdges = 0;
		}
			// constructor. initialize numVertices and numEdges to 0


		// copy constructor
		public graph(graph<T> g)
		{
			this.copyFrom(g); // copy g to current object
		}
			// copy constructor


		// overloaded assignment operator

		//---Partially obtianed from outside sources---
		//---I do not take credit for this function---
		public final graph<T> copyFrom (graph<T> cgraph)
		{
			vertexMap.iterator mi = new vertexMap.iterator();

			if (this == cgraph)
			{
				return this;
			}

			vtxMap = new TreeMap<T,Integer>(cgraph.vtxMap);
			vInfo = new ArrayList<vertexInfo<T>>(cgraph.vInfo);
			numVertices = cgraph.numVertices;
			numEdges = cgraph.numEdges;
			availStack = new Stack<Integer>(cgraph.availStack);

			for (mi = vtxMap.iterator();mi != vtxMap.end();mi++)
			{
					vInfo.get(mi.second).vtxMapLoc = mi;
			}

			return this;
		}


		// ATTRIBUTE TESTING FUNCTIONS

		public final int numberOfVertices()
		{
			return numVertices;
		}
			// return the number of vertices in the graph

		public final int numberOfEdges()
		{
			return numEdges;
		}
			// return the number of edges in the graph

	  public final boolean empty()
	  {
		  return numVertices == 0;
	  }
			// is the graph empty?


		// ACCESS MEMBER FUNCTIONS

		// return the weight of the edge (v1, v2). if the edge
		// does not exist, return -1

		public final int getWeight(T v1, T v2)
		{
			// find the vInfo indices for the two vertices
			int pos1 = getvInfoIndex(v1);
			int pos2 = getvInfoIndex(v2);

			// check for an error
			if (pos1 == -1 || pos2 == -1)
			{
				// if v1 or v2 not in list of vertices, throw an exception
				throw graphError("graph getWeight(): vertex not in the graph");
			}

			// construct an alias for the edge list in vInfo[pos1]
			final TreeSet<neighbor> edgeSet = vInfo.get(pos1).edges;
			Iterator<neighbor> setIter;

			// search for pos2 in the edge list and return its weight
			// if found; otherwise, return -1 to indicate that the
			// edge does not exist
			/*if ((setIter = edgeSet.find(new neighbor(pos2))) != edgeSet.end())
			{
				return (*setIter).weight;
			}
			else
			{
				return -1;
			}*/
			while(setiter != edgeSet.end())
			{
			  if(setIter = edgeSet.find(new neighbor(pos2)))
			    return setIter.weight;
			  else
				return -1;
			}
			
		}
			// return the weight of the edge (v1, v2). if the edge.
			// does not exist, return -1
			// Precondition: v1 and v2 are vertices in the graph. if not
			// the function throws the graphError exception

		public final void setWeight(T v1, T v2, int w)
		{
			// find the vInfo indices for the two vertices
			int pos1 = getvInfoIndex(v1);
			int pos2 = getvInfoIndex(v2);

			// check for an error
			if (pos1 == -1 || pos2 == -1)
			{
				// if v1 or v2 not in list of vertices, throw an exception
				throw graphError("graph setWeight(): vertex not in the graph");
			}

			// construct an alias for the edge list in vInfo[pos1]
			TreeSet<neighbor> edgeSet = vInfo.get(pos1).edges;
			Iterator<neighbor> setIter;

			// search for pos2 in the edge list and update its weight.
			// if the edge does not exist, throw an exception
			/*if ((setIter = edgeSet.find(new neighbor(pos2))) != edgeSet.end())
			{
				(*setIter).weight = w;
			}
			else
			{
				throw graphError("graph setWeight(): edge not in the graph");
			}*/
			while(setiter != edgeSet.end())
			{
			  if(setIter = edgeSet.find(new neighbor(pos2)))
			    setIter.weight = w;
			  else
				throw graphError("graph setWeight(): edge not in the graph");
			}
			
		}
			// update the weight of edge (v1, v2).
			// Precondition: v1 and v2 are vertices in the graph. if not,
			// the function throws the graphError exception
			// Postcondition: the weight of vertex (v1,v2) is w


		// return the number of edges entering  v
		public final int inDegree(T v)
		{
			// find the vInfo index for v
			int pos = getvInfoIndex(v);

			if (pos != -1)
			{
				// in-degree is stored in vInfo[pos]
				return vInfo.get(pos).inDegree;
			}
			else
			{
				// throw an exception
				throw graphError("graph inDegree(): vertex not in the graph");
			}
		}
			// return the number of edges entering  v.
			// Precondition: v is a vertex in the graph. if not,
			// the function throws the graphError exception


		// return the number of edges leaving  v
		public final int outDegree(T v)
		{
			// find the vInfo index for v
			int pos = getvInfoIndex(v);

			if (pos != -1)
			{
				// out-degree is number of elements in the edge set
				return vInfo.get(pos).edges.size();
			}
			else
			{
				// throw an exception
				throw graphError("graph outDegree(): vertex not in the graph");
			}
		}
			// return the number of edges leaving  v.
			// Precondition: v is a vertex in the graph. if not,
			// the function throws the graphError exception


	  // return the list of all adjacent vertices
	  public final TreeSet<T> getNeighbors(T v)
	  {
		  // set returned
		  TreeSet<T> adjVertices = new TreeSet<T>();

		  // obtain the position of v from the map
		  int pos = getvInfoIndex(v);

		  // if v not in list of vertices, throw an exception
		  if (pos == -1)
		  {
			  throw graphError("graph getNeighbors(): vertex not in the graph");
		  }

		  // construct an alias for the set of edges in vertex pos
		  final TreeSet<neighbor> edgeSet = vInfo.get(pos).edges;
		  // use setIter to traverse the edge set
		  Iterator<neighbor> setIter;

		  // index of vertexInfo object corresponding to an adjacent vertex
		  int aPos;

		  for (setIter = edgeSet.iterator(); setIter.hasNext();)
		  { // "(*setIter).dest" is index into vInfo
			  aPos = (setIter.next()).dest;
			  // insert vertex data into a set. vInfo[aPos].vtxMapLoc"
			  // is a map iterator. dereference it to access the vertex
			  adjVertices.add((vInfo.get(aPos).vtxMapLoc).first);
		  }

		 return adjVertices;
	  }
			// return a set containing the neighbors of v.
			// Precondition: v is a vertex in the graph. if not,
			// the function throws the graphError exception


		// GRAPH MODIFICATION MEMBER FUNCTIONS

		// add the edge (v1,v2) with specified weight to the graph
		public final void insertEdge(T v1, T v2, int w)
		{
			// obtain the vInfo indices
			int pos1 = getvInfoIndex(v1);
			int pos2 = getvInfoIndex(v2);

			// check for an error
			if (pos1 == -1 || pos2 == -1)
			{
				// if v1 or v2 not in list of vertices, throw an exception
				throw graphError("graph insertEdge(): vertex not in the graph");
			}
			else if (pos1 == pos2)
			{
				// we do not allow self-loops
				throw graphError("graph insertEdge(): self-loops are not allowed");
			}


			// attempt to insert edge (pos2,w) into the edge set of vertex pos1
			Pair<Iterator<neighbor>, Boolean> result = vInfo.get(pos1).edges.add(new neighbor(pos2, w));

			// make sure edge was not already in the set
			if (result.second)
			{
				// increment the number of edges
				numEdges++;
				// the in-degree of v2 is one more
				vInfo.get(pos2).inDegree++;
			}
		}
			// add the edge (v1,v2) with specified weight to the graph.
			// Precondition: v1 and v2 are vertices in the graph. if not,
			// the function throws the graphError exception
			// Postcondition: The number of edges increases by 1


		// insert v into the graph
		public final void insertVertex(T v)
		{
			int index;

			// attempt to insert v into the map with index 0.
			// if successful, insert an iterator pointing at it
			// into the vertex list at location index. index is obtained
			// from the availability stack or by creating a new entry
			// at the back of the vector. fix the map entry to refer
			// to index and increment numVertices. if the insertion did
			// not take place, the vertex already exists. generate an
			// exception
			Pair<typename vertexMap.iterator, Boolean> result = vtxMap.insert(typename vertexMap.value_type(v,0));
			if (result.second)
			{
				// see if there is an entry in vInfo freed by an earlier
				// call to eraseVertex()
				if (!availStack.empty())
				{
					// yes. get its index
					index = availStack.peek();
					availStack.pop();
					// call to constructor builds a empty edge set
					vInfo.set(index, new vertexInfo<T>(result.first));
				}
				else
				{
					// no. we'll have to increase the size of vInfo
					vInfo.add(new vertexInfo<T>(result.first));
					index = numVertices;
				}

				result.first.second = index;
				numVertices++;
			}
			else
			{
				throw graphError("graph insertVertex(): vertex already in the graph");
			}
		}
			// insert v into the graph.
			// Precondition: v is a vertex in the graph. if not,
			// the function throws the graphError exception.
			// Postcondition: the number of vertices increases by 1


		// erase edge (v1,v2) from the graph
		public final void eraseEdge(T v1, T v2)
		{
			// obtain the indices of v1 and v2 in vInfo
			int pos1 = getvInfoIndex(v1);
			int pos2 = getvInfoIndex(v2);

			// check for an error
			if (pos1 == -1 || pos2 == -1)
			{
				// if v1 or v2 not in list of vertices, throw an exception
				throw graphError("graph eraseEdge(): vertex not in the graph");
			}

			// construct an alias to the edge set of vInfo[pos1]
			TreeSet<neighbor> edgeSet = vInfo.get(pos1).edges;
			Iterator<neighbor> setIter;

			// search for pos2 in the edge set
			setIter.copyFrom(edgeSet.find(new neighbor(pos2)));
			// if pos2 is in the set, erase it; otherwise, output an
			// error message
			if (setIter != edgeSet.end())
			{
				edgeSet.erase(setIter);
				// the in-degree of v2 is one less
				vInfo.get(pos2).inDegree--;
				numEdges--;
			}
			else
			{
				throw graphError("graph eraseEdge(): edge not in the graph");
			}
		}
			// erase edge (v1,v2) from the graph
			// Precondition: v1 and v2 are vertices in the graph. if not,
			// the function throws the graphError exception.
			// Postcondition: The number of edges decreases by 1

	  public final void eraseVertex(T v)
	  {
		  // use to search for and remove v from the map
		  vertexMap.iterator mIter = new vertexMap.iterator();
		  // pos is index of v in the vertex list
		  int pos;
		  int j;
		  // used in removal of edges to v
		  Iterator<neighbor> sIter;

		  // search the map for the key v
		  mIter = vtxMap.find(v);
		  // if vertex is not present, terminate the erase
		  if (mIter == vtxMap.end())
		  {
			  // if v not in list of vertices, throw an exception
			  throw graphError("graph eraseVertex(): vertex not in the graph");
		  }

		  // obtain the index of v in vInfo
		  pos = mIter.second;

		  // erase vertex from the map and decrement number of vertices
		  vtxMap.remove(mIter);
		  numVertices--;

		  // mark the vertex entry in vInfo as not occupied. the index pos is now
		  // available. push it on the availability stack for use later if we
		  // insert a vertex
		  vInfo.get(pos).occupied = false;
		  availStack.push(pos);

		  // cycle through vInfo and remove all edges going to v
		  for (j = 0; j < vInfo.size(); j++)
		  {
			  // skip all unoccupied entries, including pos
			  if (vInfo.get(j).occupied)
			  {
				  // construct an alias for the set vInfo[j].edges
				  TreeSet<neighbor> edgeSet = vInfo.get(j).edges;

				  sIter.copyFrom(edgeSet.iterator());
				  // cycle through the edge set
				  while (sIter.hasNext())
				  {
					  if ((sIter.next()).dest == pos)
					  {
						  // found pos. remove it from the set and
						  // decrement the edge count
						  edgeSet.erase(sIter);
						  numEdges--;
						  break;
					  }
					  else
					  {
						  // took no action. just move forward
						  sIter.next();
					  }
				  }
			  }
		  }

		  // decrement numEdges by the number of edges for vertex v
		  numEdges -= vInfo.get(pos).edges.size();

		  // the in-degree for all of v's neighbors must be decreased by 1
		  TreeSet<neighbor> edgesFromv = vInfo.get(pos).edges;
		  for (sIter = edgesFromv.iterator(); sIter.hasNext();)
		  {
			  j = (sIter.next()).dest;
			  vInfo.get(j).inDegree--;
		  }

		  // clear the edge set. construct an alias for vInfo[pos].edges
		  // and use erase to clear the set
		  TreeSet<neighbor> edgeSet = vInfo.get(pos).edges;
		  edgeSet.erase(edgeSet.iterator(), edgeSet.end());
	  }
			// erase v from the graph
			// Precondition: v is a vertex in the graph. if not,
			// the function throws the graphError exception.
			// Postconditions: The number of vertices decreases by 1,
			// and the operation removes all edges to or from v


		// erase the graph
		public final void clear()
		{
			// clear the vertex list, vertex map and the
			// availability stack
			vInfo.remove(vInfo.iterator(), vInfo.end());
			vtxMap.remove(vtxMap.iterator(), vtxMap.end());
			while (!availStack.empty())
			{
				availStack.pop();
			}

			// set the number of vertices and edges to 0
			numVertices = 0;
			numEdges = 0;
		}
			// remove all the vertices and edges from the graph


		// ITERATOR FUNCTIONS

		// each graph iterator function returns
		// the corresponding map iterator
		public final graph<T>.iterator begin()
		{
		  return graph<T>.iterator.vtxMap.iterator;
		}
		public final graph<T>.iterator end()
		{
			return graph<T>.iterator.vtxMap.end;
		}

		public final graph<T>.const_iterator begin()
		{
			return graph<T>.iterator.vtxMap.iterator;
		}

		public final graph<T>.const_iterator end()
		{
		  return graph<T>.iterator.vtxMap.end;
		}
			// iterator functions returns corresponding map iterator

// "d_galgs.h" implements the graph algorithms using inline code.
// this is necessary for the Borland C++ 5.5 compiler
///#include "d_galgs.h"

/*
		LISTING OF THE PROTOTYPES FOR THE GRAPH ALGORITHMS

		friend istream& operator>> (istream& istr, graph<T>& g);
			// input a graph

		friend ostream& operator<< (ostream& ostr, const graph<T>& g);
			// output a graph

		friend set<T> bfs(graph<T>& g, const T& sVertex);
			// perform the breadth-first traversal from sVertex and
			// return the set of visited vertices

		friend int shortestPath(graph<T>& g, const T& sVertex,
										const T& eVertex, list<T>& path);
			// use the breadth-first traversal algorithm to determine the
			// minimum number of edges in any path from sVertex to eVertex
			// or -1 if no path exists. if a path exists, the list path
			// is the sequence of vertices

		friend int minimumPath(graph<T>& g, const T& sVertex, const T& eVertex,
									  list<T>& path);
			// find the path with minimum total weight from sVertex to eVertex
			// and return the minimum weight

		friend int minSpanTree(graph<T>& g, graph<T>& MST);
			// find the minimum spanning tree for the strongly connected digraph g

		friend bool acyclic(graph<T>& g);
			// determine if the graph is acyclic

		friend void dfsVisit(graph<T>& g, const T& sVertex, list<T>& dfsList,
									bool checkForCycle);
			// depth-first visit assuming a WHITE starting vertex. dfsList
			// contains the visited vertices in reverse order of finishing time.
			// when checkForCycle is true, the function throws an exception if
			// it detects a cycle

		friend void dfs(graph<T>& g, list<T>& dfsList);
			// depth-first search. dfsList contains all the graph vertices in the
			// reverse order of their finishing times

		friend void topologicalSort(graph<T>& g, list<T>& tlist);
			// find a topological sort of an acyclic graph

		friend graph<T> transpose(graph<T>& g);
			// return the transpose of the graph

		friend void strongComponents(graph<T>& g, vector<set<T> >& component);
			// find the strong components of the graph
*/


		private TreeMap<T,Integer> vtxMap = new TreeMap<T,Integer>();
			// store vertex in a map with its name as the key and the index
			// of the corresponding vertexInfo object in the vInfo
			// vector as the value

		private Vector<vertexInfo<T>> vInfo = new Vector<vertexInfo<T>>();
			// list of vertexInfo objects corresponding to the vertices

		private int numVertices;
		private int numEdges;
			// current size (vertices and edges) of the graph

		private Stack<Integer> availStack = new Stack<Integer>();
			// availability stack for storing unused indices in vInfo


		// uses vtxMap to obtain the index of v in vInfo

		private int getvInfoIndex(T v)
		{
			// iter used in map lookup
			vertexMap.const_iterator iter = new vertexMap.const_iterator();
			// index that is returned
			int pos;

			// find the map entry with key v
			iter = vtxMap.find(v);

			// make sure v is in the map
			if (iter == vtxMap.end())
			{
				pos = -1;
			}
			else
			{
				// the index into vInfo is the value of the map entry
				pos = iter.second;
			}

			return pos;
		}
			 // uses vtxMap to obtain the index of v in vInfo
                 
//000000000000000000000000000000000000000000000000000000000000000000000000000000//

// perform the breadth-first traversal from sVertex and
// return the set of visited vertices
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


//00000000000000000000000000000000000000000000000000000000000000000000//
                 

// depth-first visit assuming a WHITE starting vertex. dfsList
// contains the visited vertices in reverse order of finishing time.
// when checkForCycle is true, the function throws an exception if
// it detects a cycle
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

// depth-first search. dfsList contains all the graph vertices in the
// reverse order of their finishing times
private void dfs(graph<T> g, LinkedList<T> dfsList)
{
	int i;

	// clear dfsList
	dfsList.remove(dfsList.iterator(), dfsList.end());

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
			dfsVisit(g,(g.vInfo[i].vtxMapLoc).first, dfsList, false);
		}
	}
}
                 
}