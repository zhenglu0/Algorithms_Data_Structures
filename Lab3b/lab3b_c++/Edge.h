// EDGE.H
// Edge class for the multigraph
//
// A (directed) edge contains four values: a unique identifier, a
// "from" vertex, a "to" vertex, and an integer weight.  Subclass Edge 
// if you want to store more complicated info.

#ifndef __EDGE_H
#define __EDGE_H

#include <iostream>

#include "Vertex.h"

class Edge {

public:
    Edge(int id, Vertex *from, Vertex *to, int weight)
    {
        _id = id;
        _from = from;
        _to = to;
        _weight = weight;
    }
  
    int id() const { return _id; }
     
    Vertex *from() const { return _from; }
     
    Vertex *to() const { return _to; }

    int weight() const { return _weight; }
  
private:
    Vertex *_from, *_to;
    int _weight;
    int _id;
    
};


// print an edge
inline std::ostream &operator<<(std::ostream &os, const Edge &edge)
{
    os << edge.id() << ": " << *edge.from() << " --> " 
     << *edge.to() << ", " << edge.weight() << ')';
    return os;
}

#endif
