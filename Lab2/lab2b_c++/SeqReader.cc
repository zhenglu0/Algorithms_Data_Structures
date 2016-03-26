// SEQREADER.CC
// Read a sequence from a file.  The file is assumed to contain a single
// sequence, possibly split across multiple lines.  Case is not preserved.
//

#include "SeqReader.h"

#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

const char *readSeq(const char *fileName, int *iseqLength)
{
    ifstream is(fileName);
    vector<char> buffer;
  
    if (!is)
    {
        cout << "Error: could not open file " << fileName << endl;
        return NULL;
    }
  
    // Accumulate the sequence in a buffer (minus any whitespace).
    // Convert to lower case as we read.
    //
    while (is && !is.eof())
    {
        char c;
      
        is.get(c);
        if (!is.eof() && c != '\n')
        buffer.push_back(tolower(c));
    }
  
    char *seq = new char [buffer.size() + 1];
    for (unsigned int j = 0; j < buffer.size(); j++)
    seq[j] = buffer[j];
  
    seq[buffer.size()] = 0;
    *iseqLength = (int) buffer.size();
  
    return seq;
}
