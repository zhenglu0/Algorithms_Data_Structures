//
// EVENTLIST.CC
// Skeleton code for your EventList collection type.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>

#include "EventList.h"
#include "Item.h"

using namespace std;

#define MINYEAR -9999
#define MAXYEAR 9999

////////////////////////////////////////////////////////////////////
// Here's a suitable geometric random number generator for choosing
// pillar heights.  We treat the middle bit of each random number
// generated as a random coin flip.
////////////////////////////////////////////////////////////////////

int EventList::randomHeight() {
    int v = 1;
    while ((random() >> 16) & 0x01) { v++; }
    return v;
}

////////////////////////////////////////////////////////////////////
// Methods for the Lab
////////////////////////////////////////////////////////////////////

//
// Constructor
//
EventList::EventList() {
    srandom(8725); // you may seed the PRNG however you like.
    height = 0;
    evHead = new Event(MINYEAR, "");
    evTail = new Event(MAXYEAR, "");
    head = new Item(evHead, 1);	// min year is a low year 1 is the size
    tail = new Item(evTail, 1);	// max is a high year 1 is the size
    for(int i = 0; i < head->nextArrayLength; i++) {
        head->next[i] = tail;
    }
    m = new map<std::string,std::vector<Event *> >;
}


//
// Destructor
//
EventList::~EventList() {
    delete head; delete tail;
    delete evHead; delete evTail;
    delete m;
}


//
// Add an Event to the list.
//
void EventList::insert(Event *e) {
    putEventsKeyWordsIntoMap(e); // break into Events KeyWords Into Map
    int h = height;	// store the height, the level information
    Item *itemPtr = head; // item pointer
    Item **update = new Item* [h+1];
    int updateArrayLength = h+1; // the size of the next array
    memset(update, 0, sizeof(Item*)*updateArrayLength); 
    // initialize pointers
    vector<Event *> *elPtr = NULL; // defines event list pointer
    while (h >= 0) {
        elPtr = itemPtr->next[h]->eventList;
        if ((*elPtr)[0]->year == e->year) {
            elPtr->push_back(e);
            return;
        }
        if ((*elPtr)[0]->year < e->year) {
            itemPtr = itemPtr->next[h];	// go to the place
        } else {
            update[h] = itemPtr;
            h--;
        }
    }
    // just reuse h, h is new node height
    int newItemHeight = randomHeight();	
    // for double sizing
    while (head->nextArrayLength <= newItemHeight) {
        int storeOldHeadLength = head->nextArrayLength;
        // previous variables
        Item *previousHead = head;
        // the new variables, we only need to update the head
        head = new Item (evHead, 2*head->nextArrayLength-1);
        // update the update[]
        for (int i = 0; i < updateArrayLength; i++) {
            if (update[i] == previousHead)
                update[i] = head;
        }
        // update new head
        for (int i = 0; i < storeOldHeadLength; i++) {
            head->next[i] = previousHead->next[i];
        }
        // already cover the first part of array, 
        // now handle the second
        for (int i = storeOldHeadLength; 
            i < head->nextArrayLength; i++) {
            head->next[i] = tail;
        }
        delete previousHead;
    }
    // update height information
    height = newItemHeight > height ? newItemHeight : height;
    itemPtr = new Item(e, newItemHeight);
    for (int i = 0; i <= newItemHeight; i++) {
        if (i < updateArrayLength) {
            itemPtr->next[i] = update[i]->next[i];
            update[i]->next[i] = itemPtr;
        } else {
            head->next[i] = itemPtr;
            itemPtr->next[i] = tail;
        }
    }
    delete [] update;
}


//
// Remove all Events in the list with the specified year.
//
void EventList::remove(int year) {
    int h = height;	// store the height
    Item *itemPtr = head; // item pointer
    Item **update = new Item* [height + 1];
    vector<Event *> *elPtr = NULL; // defines event list pointer
    while (h >= 0) {
        elPtr = itemPtr->next[h]->eventList;
        if((*elPtr)[0]->year < year) {
            itemPtr = itemPtr->next[h];	// go to the place
        } else {
            update[h] = itemPtr;
            h--;
        }
    }
    itemPtr = itemPtr->next[0];
    elPtr = itemPtr->eventList;
    // if the element is not in the array
    if((*elPtr)[0]->year != year)
        return;
    // if we found the element
    for (int i = 0; i < itemPtr->nextArrayLength; i++) {
        update[i]->next[i] = itemPtr->next[i];
    }
    // check if we need to update the height
    if (itemPtr->nextArrayLength-1 == height) {
        elPtr = head->next[height]->eventList;
        while ((*elPtr)[0]->year == MAXYEAR)
            height--;
    }
    delete [] update;
    delete itemPtr;
}


//
// Find all events with greatest year <= input year.
//
vector<Event *> *EventList::findMostRecent(int year) {
    int h = height;
    Item *itemPtr = head; // item pointer
    vector<Event *> *elPtr = NULL; // defines event list pointer
    while (h >= 0) {
        elPtr = itemPtr->next[h]->eventList;
        if((*elPtr)[0]->year < year)
            itemPtr = itemPtr->next[h];	// go to the place
        else
            h--;
    }
    // check if there is equal condition
    if ((*elPtr)[0]->year == year)
        itemPtr = itemPtr->next[0];
    // declare some variable
    int length = itemPtr->eventList->size();
    vector<Event *>  *mostRecentEvent = new vector<Event *>;
    for(int i = 0; i < length; i++) {
        mostRecentEvent->push_back((*(itemPtr->eventList))[i]);
    }
    return mostRecentEvent;
}


//
// Find all Events within the specific range of years (inclusive).
//
vector<Event *> *EventList::findRange(int first, int last)
{
    int h = height;
    Item *itemPtr = head; // item pointer
    vector<Event *> *elPtr = NULL; // defines event list pointer
    while (h >= 0) {
        elPtr = itemPtr->next[h]->eventList;
        if((*elPtr)[0]->year < first)
            itemPtr = itemPtr->next[h];	// go to the place
        else
            h--;
    }
    itemPtr = itemPtr->next[0];
    vector<Event *> *rangeOfEvents = new vector <Event* >;
    elPtr = itemPtr->eventList;
    while((*elPtr)[0]->year <= last) {
        for(unsigned int i = 0; i < elPtr->size(); i++) {
            rangeOfEvents->push_back((*elPtr)[i]);
        }
        itemPtr = itemPtr->next[0];
        elPtr = itemPtr->eventList;
    }
    return rangeOfEvents;
}


//
// Find all events whose descriptions have the specified keyword,
// and return them in chronological order.
//
vector<Event *> *EventList::findByKeyword(const string &keyword) {
    const string key = keyword;
    map<string,vector<Event *> >::iterator it;
    it = m->find(key);
    if (it == m->end())
        return NULL;
    else {
        vector<Event *> *copy = new vector<Event *> (it->second);
        return copy;
    }
}

void EventList::putEventsKeyWordsIntoMap(Event *e) {
    vector<string> v = e->toKeyWords();
    string key;
    map<string,vector<Event *> >::iterator it;
    for (unsigned int i = 0; i < v.size(); i++) {
        key = v[i];
        it = m->find(key);
        // if we did not find the key in the map
        if (it == m->end()) {
            vector <Event *> v;
            m->insert(pair<string,vector<Event *> >(key,v));
            v.push_back(e);
        } else {
            // if we find the key in the map
            (it->second).push_back(e);
        }
    }
}


