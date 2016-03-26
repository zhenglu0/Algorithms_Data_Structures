#ifndef __STRINGTABLE_H
#define __STRINGTABLE_H

#include "Record.h"
#include <iostream>

using namespace std;

class LinkedHashEntry {
public:
    LinkedHashEntry(Record *r) {
        this->r= r;
        this->next = NULL;
    }
    Record* getRecord() { return r; }
    LinkedHashEntry *getNext() { return next; }
    void setNext(LinkedHashEntry *next) { this->next = next; }

private:
    Record* r;
    LinkedHashEntry *next;
};

class StringTable {
    
public:
    StringTable(int maxSize, int matchLength);
    bool insert(Record *r);
    void remove(Record *r);
    Record *find(const char *key);
    
private:
    int matchLength;
    LinkedHashEntry **table; // used to store the record
    int toHashKey(const char *s) const;
    int m; // the the number of slots
};

#endif
