//
// EVENTREADER.CC
// Implements the EventReader class
//

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "EventReader.h"
#include "Tokenizer.h"

using namespace std;

const char spaces[] = " \r\t";

//
// top-level event reader
//
vector<Event *> *EventReader::readEvents(const char *fileName)
{
  string nextLine;
  
  vector<Event *> *v = new vector<Event *>;
  
  ifstream is(fileName);
  if (!is)
    {
      cerr << "Error opening event file " << fileName << '\n';
      return v;
    }
  
  // Read each event, one per line.
  while (is)
    {
      getline(is, nextLine);
      if (nextLine.find_first_not_of(spaces) != string::npos)
	{
	  Event *e = parseEvent(nextLine);
	  if (e != NULL) 
	    v->push_back(e);
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
// parseEvent()
// Parse a single event from a line read from the event file.
// Return NULL if we cannot parse the event.
//
Event * EventReader::parseEvent(const string &eventString)
{
  Tokenizer t(eventString);
  
  int date = strtol(t.nextToken().c_str(), NULL, 10);
  
  string rest = t.rest();
  size_t leftTrim = rest.find_first_not_of(spaces);
  if (leftTrim == string::npos)
    {
      rest = "";
      leftTrim = 0;
    }
  
  return new Event(date, rest.substr(leftTrim)); 
}
