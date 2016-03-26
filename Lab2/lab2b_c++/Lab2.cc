
// LAB2.CC
// Sequence matching driver for CSE 241 Lab 2
//
// SYNTAX: Lab2 <match length> <corpus file> <pattern file> [ <mask file> ]
//
// This sequence matching program reads two sequences, a CORPUS and a
// PATTERN, from files on disk and finds all strings of a given match
// length M that occur in both corpus and pattern.
// Matching substrings are printed in the form
//      <index 1> <index 2> <substring>
// where the two indices are the offsets of the match within the corpus and
// pattern, respectively, and <substring> is the actual matching string.
//
// As an optional third argument, the program can take a file containing a
// MASK sequence.  Substrings of the mask sequence are considered
// "uninteresting" and so must not be reported by the matching code.
// To implement this requirement, we delete any occurrences of substrings
// in the mask sequence from our pattern table before performing the search.
//

#include "SeqReader.h"
#include "StringTable.h"

#include <iostream>
#include <cstdlib>

using namespace std;


//
// local prototypes
//
static StringTable *createTable(const char *patternSeq, int patternLength,
				int matchLength);
static void maskTable(StringTable *table, const char *maskSeq, int maskLength,
		      int matchLength);
static void findMatches(StringTable *table, const char *corpusSeq, 
			int corpusLength, int matchLength);


int main(int argc, char *argv[])
{
    int matchLength        = 0;
    const char *corpusSeq  = NULL;
    const char *patternSeq = NULL;
    const char *maskSeq    = NULL;
    int corpusLength, patternLength, maskLength;
  
    if (argc < 4)
    {
        cout << "Syntax: Lab2 <match length> <corpus file> <pattern file> [<mask file>]\n";
        exit(1);
    }
    else
    {
        matchLength = strtoul(argv[1], NULL, 10);
        corpusSeq  = readSeq(argv[2], &corpusLength);
        patternSeq = readSeq(argv[3], &patternLength);

        cout << "M = " << matchLength << '\n';
        cout << "CORPUS: "  << corpusLength << " bases\n";
        cout << "PATTERN: " << patternLength << " bases\n";
      
        if (argc > 4)
        {
            maskSeq = readSeq(argv[4], &maskLength);
            cout << "MASK: "  << maskLength << " bases\n";
        }
    }
  
    StringTable *table = createTable(patternSeq, patternLength, matchLength);
    
    if (maskSeq != NULL)
        maskTable(table, maskSeq, maskLength, matchLength);
    
    findMatches(table, corpusSeq, corpusLength, matchLength);
  
    return 0;
}


// Create a new StringTable containing all substrings of the pattern
// sequence.
// 
static StringTable *createTable(const char *patternSeq, int patternLength,
				int matchLength)
{
    StringTable *table = new StringTable(patternLength, matchLength);

    for (int j = 0; j < patternLength - matchLength + 1; j++)
    {
        const char *key = patternSeq + j;

        Record *rec = table->find(key);
      
        if (rec == NULL) // not found -- new Record
        {
            rec = new Record(key);
            if (!table->insert(rec))
            {
                cout << "Error (insert): hash table is full!\n";
            }
        }
      
        rec->positions.push_back(j);
    }
  
    return table;
}


// Remove all substrings in the mask sequence from a StringTable.
// 
static void maskTable(StringTable *table, const char *maskSeq, int maskLength,
		      int matchLength)
{
    for (int j = 0; j < maskLength - matchLength + 1; j++)
    {
        const char *key = maskSeq + j;
      
        Record *rec = table->find(key);
        if (rec != NULL)
        {
            table->remove(rec);
            delete rec;          // don't need this struct anymore
        }
    }
}


// Find and print all matches between the corpus sequence and any
// string in a StringTable.
//
static void findMatches(StringTable *table, const char *corpusSeq, 
			int corpusLength, int matchLength)
{
    for (int j = 0; j < corpusLength - matchLength + 1; j++)
    {
        const char *key = corpusSeq + j;
      
        const Record *rec = table->find(key);
        if (rec != NULL)
        {
            for (unsigned int k = 0; k < rec->positions.size(); k++)
            {
                cout << j << ' ' << rec->positions[k] << ' ';
                for (int p = 0; p < matchLength; p++)
                    cout << key[p];
                cout << '\n';
            }
        }
    }
}
