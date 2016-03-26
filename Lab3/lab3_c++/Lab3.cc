//
// LAB3.CC
// CSE241 Lab 3 Driver Code
//
// This driver code exercises your EventList collection type.
//
// The driver's command line syntax is:
//
//    Lab3 <event file> <query file>
// 
// where <event file> is a file of events, and <query file> is a file
// of queries on the event list
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <cctype>

#include "EventList.h"
#include "EventReader.h"
#include "Query.h"
#include "QueryReader.h"

using namespace std;

// local prototypes
static void RunTest(EventList *list, const char *queryFileName);


static bool EventComparator (Event *e1, Event *e2)
{
  if (e1->year == e2->year)
    return (e1->description.compare(e2->description) < 0);
  else 
    return (e1->year < e2->year);
}


int main(int argc, char *argv[])
{
  if (argc < 3)
    {
      cerr << "Syntax: Lab3 <event file> <query file>\n";
      exit(1);
    }
  
  vector<Event *> *events = EventReader::readEvents(argv[1]);
  if (events == NULL) // I/O error
    exit(1);
  
  EventList *list = new EventList();
  
  //
  // Enter the elements into the event list
  //
  for (unsigned int j = 0; j < events->size(); j++)
    list->insert((*events)[j]);
  
  RunTest(list, argv[2]);

  //
  // Clean up and quit
  //
  
  delete list;
  
  for (unsigned int j = 0; j < events->size(); j++)
    delete (*events)[j];
  delete events;
  
  return 0;
}


//
// This is an interactive test interface for your event list.
// If you want to run some specific commands as a test case, 
// feel free to replace this code with a procedure (but please
// print the command before you run it, so that the TAs and I
// can see what you did).
//
static void RunTest(EventList *list, const char *queryFileName)
{
  vector<Query *> *queries = QueryReader::readQueries(queryFileName);
  if (queries == NULL) // I/O error
    exit(1);
  
  for (unsigned int j = 0; j < queries->size(); j++)
    {
      vector<Event *> *el;
      string kw;
      
      Query *q = (*queries)[j];
      
      cout << "> " << *q << '\n';
      
      switch (q->command)
	{
	case Query::FINDRANGE:
	  el = list->findRange(q->year1, q->year2);
	  if (el == NULL)
	    cout << "No events found.\n";
	  else
	    {
	      sort(el->begin(), el->end(), EventComparator);
	      for (unsigned int k = 0; k < el->size(); k++)
		cout << *((*el)[k]) << '\n';
	      
	      delete el;
	    }
	  break;
	  
	case Query::FINDMOSTRECENT:
	  el = list->findMostRecent(q->year1);
	  if (el == NULL)
	    cout << "No events found.\n";
	  else
	    {
	      sort(el->begin(), el->end(), EventComparator);
	      for (unsigned int k = 0; k < el->size(); k++)
		cout << *((*el)[k]) << '\n';
	      
	      delete el;
	    }
	  break;
	  
	case Query::FINDKEYWORD:
	  kw = q->keyword;
	  for (unsigned int k = 0; k < kw.length(); k++)
	    kw[k] = tolower(kw[k]);
	  
	  el = list->findByKeyword(kw);
	  if (el == NULL)
	    cout << "No events found.\n";
	  else
	    {
	      sort(el->begin(), el->end(), EventComparator);
	      for (unsigned int k = 0; k < el->size(); k++)
		cout << *((*el)[k]) << '\n';
	      
	      delete el;
	    }
	  break;
	  
	case Query::DELETE:
	  list->remove(q->year1);
	  break;
	}
      
      cout << "\n";
    }
  
  for (unsigned int j = 0; j < queries->size(); j++)
    delete (*queries)[j];
  delete queries;
}
