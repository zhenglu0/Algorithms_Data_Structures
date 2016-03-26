//
// EVENTLIST.H
// Interface for your EventList collection type.
//

#ifndef __EVENTLIST_H
#define __EVENTLIST_H

#include <vector>
#include <string>
#include <map>

#include "Event.h"
#include "Item.h"

class EventList {
public:
    EventList();
    ~EventList();

    //
    // Add an Event to the list.
    //
    void insert(Event *e);

    //
    // Remove all Events in the list with the specified year.
    //
    void remove(int year);

    //
    // Find all events with greatest year <= input year
    //
    std::vector<Event *> *findMostRecent(int year);

    //
    // Find all Events within the specific range of years (inclusive).
    //
    std::vector<Event *> *findRange(int first, int last);

    ///////////////////////////////////////////////////////////////////

    //
    // Find all events whose descriptions have the specified keyword,
    // and return them in chronological order.
    //
    std::vector<Event *> *findByKeyword(const std::string &keyword);
    //
    // insert token into map, key is the token, value if the pointer
    // vector<Event *> if the map already contains the event, we
    // just push the event* into the vector
    void putEventsKeyWordsIntoMap(Event *e);
    
private:
    int randomHeight();
    int height; // store the height, the level information
    
    // head and tail pillar, actually the size of next array
    // in tail does not have to grow, it can remain one.
    // we need to only update the head next[] size
    Item *head,*tail; 
    Event *evHead,*evTail; // A dummy node like place holder
    // the map contains keywords to events
    std::map<std::string,std::vector<Event *> > *m;
};

#endif
