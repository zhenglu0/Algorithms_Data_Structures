//
// SHORTESTPATHS.CC
// Compute shortest paths in a graph.
//
// Your constructor should compute the actual shortest paths and
// maintain all the information needed to reconstruct them.  The
// returnPath() function should use this information to return the
// appropriate path of edge ID's from the start to the given end.
//
// Note that the start and end ID's should be mapped to vertices using
// the graph's get() function.
//

#include "ShortestPaths.h"
#include "Vertex.h"
#include "Edge.h"
#include "Handle.h"
#include "PriorityQueue.h"
#include "PrettyTime.h"

#include <limits>

using namespace std;

// check whether we need the relaxation step, if I
// use numeric_limits<int>::max(), d[u->id()] + e->weight()
// may overflow for some on reachable vetext whose d[i] is infinity, 
// so I have to use
// something like numeric_limits<int>::max()/2
// also none of the edeg weight is larger than numeric_
// limits<int>::max()/2
const int INFINITY = numeric_limits<int>::max()/2;

//
// constructor
//
ShortestPaths::ShortestPaths(const Multigraph *G, int startId,
                             const Input *input, int startTime)
                            :_startId(startId),p(G->nVertices(),NULL)
{
    // 1.
    // if the startTime argument passed to the constructor is 0,
    // you should use the non-layover-aware shortest path algorithm
    // of the previous section.
    if (startTime == 0)
    {
        // delcare a handdle array to for decrease key later
        Handle **h = new Handle* [G->nVertices()];
        // declare a pointer point to the array which 
        // stores the distance
        int *d = new int[G->nVertices()];
        // declare a min priority queue
        PriorityQueue <Vertex> q;
        
        // the d[startId] should be 0
        d[startId] = 0;
        // set all the value except d[startID] to inifity first
        // and then insert them into the priority queue
        for (int i = 0; i < G->nVertices(); ++i)
        {
            if (i != startId)
            {
                d[i] = INFINITY;
                h[i] = q.insert(INFINITY,G->get(i));
            }
            else
                h[i] = q.insert(0,G->get(i));
        }
        while (!q.isEmpty())
        {
            // extract the element whose key is the smallest
            Vertex *u = q.extractMin();
            // look at all the neighbour of u, vEIter is the
            // edge iterator
            Vertex::EdgeIterator vEIter = u->adj();
            while (vEIter.hasNext())
            {
                // get the edge from u to its neighbour
                Edge *e = vEIter.next();
                // get the vertex of its neighbour
                Vertex *v = e->to();
                // check whether we need the relaxation step, if I
                // use numeric_limits<int>::max(), 
                // d[u->id()] + e->weight()
                // may overflow for some on reachable vetext whose d[i] is
                // infinity, so I have to use
                // something like numeric_limits<int>::max()/2
                if (d[v->id()] > d[u->id()] + e->weight())
                {
                    // update d[]
                    d[v->id()] = d[u->id()] + e->weight();
                    // do the decrease key operation in the priority queue
                    q.decreaseKey(h[v->id()],d[v->id()]);
                    // set v's parent u, becuase we can easily find the
                    // from vertext by call from(), and we need the edge 
                    // information in
                    // returnPath(), so we store Edge * in the vector p
                    p[v->id()] = e;
                }
            }
        }
    }
    // 2.
    // if the startTime argument passed to the constructor is NOT 0,
    // you should use the layover-aware shortest path algorithm
    // of the previous section.
    else
    {
        // delcare a handdle array to for decrease key later
        Handle **h = new Handle* [G->nVertices()];
        // declare a pointer point to the array which stores the distance
        int *d = new int[G->nVertices()];
        // declare a min priority queue
        PriorityQueue <Vertex> q;
        // we make a counter to check whether it is a starting point,
        // because the calculation of the layOver is different
        int counter = 0;
        // define the layOver time
        int layOver = 0;
        
        // the d[startId] should be 0
        d[startId] = 0;
        // set all the value except d[startID] to inifity first
        // and then insert them into the priority queue
        for (int i = 0; i < G->nVertices(); ++i)
        {
            if (i != startId)
            {
                d[i] = INFINITY;
                h[i] = q.insert(INFINITY,G->get(i));
            }
            else
                h[i] = q.insert(0,G->get(i));
        }
        while (!q.isEmpty())
        {
            // extract the element whose key is the smallest
            Vertex *u = q.extractMin();
            // look at all the neighbour of u, 
            // vEIter is the edge iterator
            Vertex::EdgeIterator vEIter = u->adj();
            // update the counter
            ++counter;
            while (vEIter.hasNext())
            {
                // get the edge from u to its neighbour
                Edge *e = vEIter.next();
                // get the vertex of its neighbour
                Vertex *v = e->to();
                // calculate layover if counter == 1, meaning 
                // that we are at the starting point
                if (counter == 1)
                    layOver = PrettyTime::elapsed(startTime, 
                                    input->flights[e->id()]->startTime);
                // if counter != 1, meaning that the starting point 
                // has been extracted
                else
                {
                    // the u that we extract must have a parent
                    if(p[u->id()])
                        layOver = 
                            PrettyTime::elapsed(
                            input->flights[p[u->id()]->id()]->endTime,
                            input->flights[e->id()]->startTime);
                }
                // check whether we need the relaxation step
                if ((d[v->id()] > d[u->id()] + e->weight() + layOver) &&
                    layOver >= 45 )
                {
                    // update d[]
                    d[v->id()] = d[u->id()] + e->weight()+ layOver;
                    // do the decrease key operation in the 
                    // priority queue
                    q.decreaseKey(h[v->id()],d[v->id()]);
                    // set v's parent u, becuase we can easily find the
                    // from vertext by call from(), and we need 
                    // the edge information in
                    // returnPath(), so we store Edge * in the vector p
                    p[v->id()] = e;
                }
            }
        }
    }
}
//
// returnPath()
// Return an array containing a list of edge ID's forming
// a shortest path from the start vertex to the specified
// end vertex.
//
vector<int> ShortestPaths::returnPath(int endId) const
{
    // store id value
    int currentId = endId;
    // use to store list of edge ID
    vector<int> v;
    // we have to make sure that p[currentId] exist, 
    // otherwise we may crash our program
    if (p[currentId])
    {
        while (currentId != _startId)
        {
            // find the parent of endId and store it in the vector
            v.push_back(p[currentId]->id());
            // update endId
            currentId = p[currentId]->from()->id();
        }
    }
    // becuase the value stored in the vector is reversed, 
    // we need to reverse it
    // declare two index, i points to from, j points to end
    int i = 0;
    int j = v.size() - 1;
    while (i < j )
    {
        // swap the value
        int temp = v[i];
        v[i++] = v[j];
        v[j--] = temp;
    }
    return v; 
}
