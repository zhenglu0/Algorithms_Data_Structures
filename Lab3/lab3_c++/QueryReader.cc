//
// QUERYREADER.CC
// Parse a file of queries against an event database.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>

#include "QueryReader.h"
#include "Tokenizer.h"

using namespace std;

const char spaces[] = " \r\t";

//
// readQueries()
// Given the name of a query file, read all the queries in
// that file and return them as a vector of ptrs to Query objects.
// If any error is encountered parsing the file, return an
// empty vector.
//
vector<Query *> *QueryReader::readQueries(const char *fileName)
{
  string nextLine;
  
  vector<Query *> *v = new vector<Query *>;
  
  ifstream is(fileName);
  if (!is)
    {
      cerr << "Error opening query file " << fileName << '\n';
      return v;
    }
  
  // Read each event, one per line.
  while (is)
    {
      getline(is, nextLine);
      if (nextLine.find_first_not_of(spaces) != string::npos)
	{
	  Query *q = parseQuery(nextLine);
	  if (q != NULL) 
	    v->push_back(q);
	  else                        // parse error
	    {
	      v->clear();
	      break;
	    }
	}
    }
  
  return v;
}
    

//
// parseQuery()
// Parse a single query from a line read from the query file.
// Return null if we cannot parse the query.
//
Query *QueryReader::parseQuery(const string &queryString)	
{
  Tokenizer t(queryString);
  
  string cmdString = t.nextToken();
  int year1, year2;
  string keyword;
  
  switch(toupper(cmdString[0]))
    {
    case 'F':
      year1 = strtol(t.nextToken().c_str(), NULL, 10);
      year2 = strtol(t.nextToken().c_str(), NULL, 10);
      return new Query(Query::FINDRANGE, year1, year2);
      
    case 'M':
      year1 = strtol(t.nextToken().c_str(), NULL, 10);
      return new Query(Query::FINDMOSTRECENT, year1);
      
    case 'K':
      keyword = t.nextToken();
      return new Query(Query::FINDKEYWORD, keyword);
      
    case 'D':
      year1 = strtol(t.nextToken().c_str(), NULL, 10);
      return new Query(Query::DELETE, year1);
    }
	    
  // default fall-through
  cout << "Unknown query type: '" << queryString << "'\n";
  return NULL;
}
