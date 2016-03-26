//
// EVENTREADER.H
// Parse a file of historical events.  Return an array
// of all parsed events as Event objects.
//
// An event file contains a list of events, one per line.  Each
// event has the form 
//
//      <year> <description>
//
// where <year> is given by an integer value (negative numbers for BC/BCE)
// and <description> is an arbitrary string (not quoted).  The two fields 
// are separated by whitespace.
//

#ifndef __EVENTREADER_H
#define __EVENTREADER_H

#include <string>
#include <vector>

#include "Event.h"

class EventReader {
public:
  
  //
  // Given the name of an event file, read all the events in
  // that file and return them as an vector of pointers to allocated
  // Event objects.  If an error is encountered parsing the file, 
  // return an empty vector.
  //
  static std::vector<Event *> *readEvents(const char *fileName);
  
private:
  
  static Event *parseEvent(const std::string &eventString);
};
  
#endif
