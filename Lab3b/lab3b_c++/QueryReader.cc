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
#include "PrettyTime.h"

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
    Query *q = new Query();

    q->startTime = PrettyTime::toTime(strtol(t.nextToken().c_str(), NULL, 10));
    q->from = t.nextToken();
  
    while (true)
    {
        string s = t.nextToken();
        if (s == "")
            break;
      
        q->tos.push_back(s);
    }
  
    return q;
}
