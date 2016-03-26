//
// VERTEX.H
// Vertex class for the multigraph
//
// A Vertex is created with an integer identifier. Subclass 
// it if you want to store more complex info.
//
// To enumerate a vertex's adjacency list, you call its adj()
// method, which returns an iterator "ei" of type EdgeIterator for 
// the list. You can call ei.hasNext() to see if there is another
// edge available, and ei.next() to get it.
//

#ifndef __VERTEX_H
#define __VERTEX_H

#include <iostream>
#include <vector>

class Edge; // forward declaration

class Vertex {
    
public:
  
    class EdgeIterator {
      
    public:
        EdgeIterator(const Vertex *iv)
        {
            v = iv;
            posn = 0;
        }
    
        bool hasNext() const { return (posn < v->neighbors.size()); }
        Edge *next() { return v->neighbors[posn++]; }
    
    private:
        const Vertex *v;
        unsigned int posn;
    };
  
    // Constructor (takes an identifier)
    Vertex(int id)
    {
        _id = id;
    }
  
  
    // id()
    // Return our identifier.
    //
    int id() const { return _id; }
    
    
    // adj()
    // Return an iterator to list all of our edges.
    //
    EdgeIterator adj() const 
    {
        EdgeIterator a(this);
        return a;
    }
  
  
    // addEdge()
    // Add an edge to our adjacency list.
    //
    void addEdge(Edge *e) 
    {
        neighbors.push_back(e);
    }
  
  
private:
  
    int _id;
    std::vector<Edge *> neighbors;
    
};


// print a vertex
inline std::ostream &operator<<(std::ostream &os, const Vertex &v)
{
    os << v.id();
    return os;
}

#endif
