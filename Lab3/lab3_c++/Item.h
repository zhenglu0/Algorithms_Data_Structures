//
// ITEM.H
// Class to be the skip list node
//

#ifndef __ITEM_H
#define __ITEM_H

#include "EventList.h"
#include <vector>
#include <cstring>

using namespace std;

class Item {

public:
    Item(Event *event, int level) {
        eventList = new vector<Event *>;
        eventList->push_back(event);
        next = new Item* [level+1];
        nextArrayLength = level+1;
        memset(next, 0, sizeof(Item*)*nextArrayLength);
    }
    ~Item() {
        delete [] next;
        delete eventList;
    }
    vector<Event *> *eventList; // store the event
    Item **next; // store the pointer information
    int nextArrayLength; // the size of the next array
};

#endif
