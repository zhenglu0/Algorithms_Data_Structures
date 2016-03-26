//
// QUERYREADER.H
// Parse a file of flight queries.  Return a vector
// of all queries as Query objects.
//
// A query has the form
//  <time> <start> <end> [<end> ....]
//
// Here, <time> is given by an integer value, while the start and each end
// are strings that represent airport names. Fields are separated
// by whitespace.

#ifndef __QUERYREADER_H
#define __QUERYREADER_H

#include <string>
#include <vector>

#include "Query.h"

class QueryReader {
    
public:
  
    //
    // Given the name of a query file, read all the queries in
    // that file and return them as an vector of pointers to allocated
    // Query objects.  If an error is encountered parsing the file, 
    // return an empty vector.
    //
    static std::vector<Query *> *readQueries(const char *fileName);
  
private:
  
    static Query *parseQuery(const std::string &queryString);
    
};
  
#endif
