//
// QUERYREADER.H
// Parse a file of queries against an event database.  Return a vector
// of all queries as Query objects.
//
// A query is one of the following:
//    F <year1> <year2>  
//        return all events between <year1> and <year2>, inclusive
//    M <year>
//        return all events in the greatest year <= <year>
//    K <word>
//        return all events whose descriptions contain the given keyword
//
//    D <year>
//        remove all events with year <year> from the database
// Here, <year> is given by an integer value (negative numbers for BC/BCE)
// and <word> is a string not containing whitespace. Fields are separated
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
