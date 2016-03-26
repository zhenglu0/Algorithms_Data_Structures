// MULTIGRAPH.H
// Multigraph class
//
// A Multigraph contains a collection of Vertex objects, each of which
// maintains its own adjacency list of edges (see the Vertex and Edge 
// classes).
//
// To enumerate the vertices in the Multigraph, you can simply ask for
// the number of vertices n, then call get() successively on 0 .. n-1.
//

#ifndef __MULTIGRAPH_H
#define __MULTIGRAPH_H

#include <vector>

#include "Vertex.h"
#include "Edge.h"

class Multigraph {

public:
  
    // nVertices()
    // Return number of vertices in graph.
    // 
    int nVertices() const
    {
        return vertices.size();
    }


    // get()
    // Return a specified vertex
    //
    Vertex *get(int id) const
    {
        return vertices[id];
    }


    // addVertex()
    // Add a vertex to the graph.
    //
    void addVertex(Vertex *v)
    {
        vertices.push_back(v);
    }
  
private:
    std::vector<Vertex *> vertices;

};

#endif
