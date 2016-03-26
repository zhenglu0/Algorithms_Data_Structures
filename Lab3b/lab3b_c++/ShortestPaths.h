//
// SHORTESTPATHS.H
// Compute shortest paths in a graph.
//

#ifndef __SHORTESTPATHS_H
#define __SHORTESTPATHS_H

#include <vector>

#include "Input.h"
#include "Multigraph.h"
#include "Edge.h"

class ShortestPaths {
    
public:
    ShortestPaths(const Multigraph *G, int startId,
    const Input *input, int startTime);
  
    std::vector<int> returnPath(int endId) const;

private:
    int _startId; // store the start id of airport
    // store the parent of a vertex, becuase we can easily find the
    // from vertext by call from(), and we need the edge information in
    // returnPath(), so we store Edge * in the vector p
    std::vector<Edge *> p; 
    
};

#endif
