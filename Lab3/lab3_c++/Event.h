//
// EVENT.H
//
// Describes a historical event via two public fields:
//  year        -- the year of the event (an integer)
//  description -- the text for the event (a string)
//
// The description of an event can be parsed into an array of keyword
// strings using the toKeywords() method.  Keywords are contiguous
// substrings of characters from the set [0-9, a-z, '-'] in the 
// description (note that the whole string is converted to lower case).
// Note that we make no attempt to remove duplicate keywords
// from the output array.  If a description contains no keywords,
// toKeywords() returns null.
//

#ifndef __EVENT_H
#define __EVENT_H

#include <iostream>
#include <vector>
#include <string>

class Event {
public:
  
  int year;                          // the year of the event
  std::string description;           // the event description
  
  // constructor
  Event(int iyear, std::string idescription)
    : year(iyear), description(idescription)
  {}
  
  // convert description to keyword array
  std::vector<std::string> toKeyWords() const;
};

// print method  
inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
  os << e.year << ' ' << e.description;
  return os;
}

#endif
