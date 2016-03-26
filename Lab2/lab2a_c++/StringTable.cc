// STRINGTABLE.CC
// A hash table mapping strings to their positions in the the pattern
// sequence You get to fill in the methods for this part.  
// Since we're passing around raw character strings, I've made 
// the match length a parameter of the hash table so we don't have to 
// keep figuring it out on each call.
//

#include "StringTable.h"

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

// Define a special record for deleted
Record *deletedRecord;

//
// Create an empty table big enough to hold maxSize records.
//
StringTable::StringTable(int maxSize, int imatchLength)
: matchLength(imatchLength),n(0),m(2)
{
    // Create an empty table big enough to hold maxSize records
    hashTable = new Record* [m];
    // Set all the entry null when initialized
    for (int i = 0; i < m; i++)
        hashTable[i] = NULL;
}


//
// Insert a Record r into the table.  Return true if
// successful, false if the table is full.  You shouldn't ever
// get two insertions with the same key value, but you may
// simply return false if this happens.
//
bool StringTable::insert(Record *r)
{
    // Calculate the key for hashing
    int k = toHashKey(r->key);
    // Set the toHashValue of the record
    r->toHashValue = k;
    // store the value of the hash function
    int s_k = baseHash(k);
	// flag to indicate over flow
	bool overFlow = true;
    // calulate the value of the hash functuion
    for (int i = 0; i < m; i++)
    {
        if (hashTable[s_k] == NULL || 
            hashTable[s_k] == deletedRecord)
        {
            hashTable[s_k] = r;
            n++; // increase the number of records in the table
			overFlow = false;
            break;
        }
        // if the table[s_k] is not NULL, calculate the 
        // multiplicative hashing
        else
            s_k = (s_k + stepHash(k)) % m;
    }
    // if the table is full
    // double the size of the hash table, 
    // and reinsert the record r, because
    // r is not successfully inserted
    if ((double)n/m > 0.25)
        doubleSizeAndReHash();
    
    if (overFlow)
        cout << r->key << endl;

	// if over flow return false, else return ture
	return ((overFlow) ? false : true);
}


//
// Delete a Record r from the table.  Note that you'll have to
// find the record first unless you keep some extra info in
// the Record structure.
//
void StringTable::remove(Record *r)
{
    // Calculate the key for hashing
    int k = toHashKey(r->key);
    // store the value of the hash function
    int s_k = baseHash(k);
    // calulate the value of the hash functuion
    for (int i = 0; i < m; i++)
    {
        // the string is not found
        if (hashTable[s_k] == NULL)
            break;
        // check if the string is what we want to find
        else if ((k == hashTable[s_k]->toHashValue) &&
                 (strncmp(r->key,hashTable[s_k]->key,
                          matchLength) == 0))
        {
            hashTable[s_k] = deletedRecord;
            break;
        }
        else
            s_k = (s_k + stepHash(k)) % m;
    }

}


//
// Find a record with a key matching the input.  Return the
// record if it exists, or NULL if no matching record is found.
//
Record *StringTable::find(const char *key)
{
    // Calculate the key for hashing
    int k = toHashKey(key);
    // store the value of the hash function
    int s_k = baseHash(k);
    // flag to indicate over flow
    Record *record_found = NULL;
    // calulate the value of the hash functuion
    for (int i = 0; i < m; i++)
    {
        // the string is not found
        if (hashTable[s_k] == NULL)
            break;
        // check if the string is what we want to find
        else if ((hashTable[s_k] != deletedRecord) &&
                 (k == hashTable[s_k]->toHashValue) &&
                 (strncmp(key,hashTable[s_k]->key,
                          matchLength) == 0))
        {
            record_found = hashTable[s_k];
            break;
        }
        else
            s_k = (s_k + stepHash(k)) % m;
    }
    // return the value
    return record_found;
}


// method to double the size of the hash talbe when table is full and
// re hash every entry in the previous table to the new table
void StringTable::doubleSizeAndReHash()
{
    int oldM = m; // value to store the old m
    m = m * 2; // double the value m
    Record **oldHashTable = hashTable; // old table
    // double sized table
    Record **doubleSizedHashTable = new Record* [m]; 
    // Set all the entry null when initialized
    for (int i = 0; i < m; i++)
    {
        doubleSizedHashTable[i] = NULL;
    }
    // find the entry and re hash into the new table
    for (int i = 0; i < oldM; i++)
    {
        if (oldHashTable[i] != NULL)
        {
            // Calculate the key for hashing
            int k = toHashKey(oldHashTable[i]->key);
            // calulate the value of the hash functuion
            int s_k = baseHash(k);
            // hash the previous record
            for (int j = 0; j < m; j++)
            {
                if (doubleSizedHashTable[s_k] == NULL)
                {
                    doubleSizedHashTable[s_k] = oldHashTable[i];
                    break;
                }
                // if the table[s_k] is not NULL, 
                // calculate the multiplicative hashing
                else
                    s_k = (s_k + stepHash(k)) % m;
            }
        }
    }
	// delete the oldHashTalbe
    delete [] oldHashTable;
	// assign the double sized table to the hashTable
    hashTable = doubleSizedHashTable;
}


//////////////////////////////////////////////////////////

// Convert a string key into an integer that serves as input to hash
// functions.  This mapping is based on the idea of a 
// linear-congruential
// pesudorandom number generator, in which successive values r_i are
// generated by computing
//    r_i = ( A * r_(i-1) + B ) mod M
// A is a large prime number, while B is a small increment thrown in
// so that we don't just compute successive powers of A mod M.
//
// We modify the above generator by perturbing each r_i, adding in
// the ith character of the string and its offset, to alter the
// pseudorandom sequence.
//
int StringTable::toHashKey(const char *s) const
{
    int A = 1952786893;
    int B = 367257;
    int v = B;

    for (int j = 0; j < matchLength; j++)
        v = A * (v + int(s[j]) + j) + B;

    if (v < 0) v = -v;
        return v;
}


int StringTable::baseHash(int hashKey) const
{
    // initialize virable k
    int k = hashKey;
    // irrational number A
    double A = (sqrt(5.0) - 1)/2;
    // calculate the result
    int h_k = int(m * (k * A - (int)(k * A)));
    // return the value of h_k
	return h_k;
}


int StringTable::stepHash(int hashKey) const
{
    // initialize virable k
    int k = hashKey;
    // irrational number A
    double A = sqrt(3.0)/2;
    // calculate the result
    int h_k = int(m * (k * A - (int)(k * A)));
    // if h_k is even, return h_k+1, because h_k had better 
    // be an odd number
	return ((h_k % 2 == 0)? h_k + 1:h_k);
}


