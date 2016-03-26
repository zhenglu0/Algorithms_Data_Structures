#ifndef __STRINGTABLE_H
#define __STRINGTABLE_H

#include "Record.h"

class StringTable {
    
public:
    StringTable(int maxSize, int matchLength);
    bool insert(Record *r);
    void remove(Record *r);
    Record *find(const char *key);
    void doubleSizeAndReHash(); // method to double the size of the hash talbe when table is full
    
private:
    int matchLength;
    int n; // stores number of records in the talbe
    int m; // the the number of slots
    Record **hashTable; // used to store the record
    int toHashKey(const char *s) const;
    int baseHash(int hashKey) const;
    int stepHash(int hashKey) const;
};

#endif
