//
// EVENT.CC
// Implements the Event class
//

#include <cctype>

#include "Event.h"
#include "Tokenizer.h"

using namespace std;
 
//
// convert description of an event to a keyword array
//
vector<string> Event::toKeyWords() const
{
  // xform input string to lower-case
  string dsc = description;
  for (string::size_type j = 0; j < dsc.length(); j++)
    dsc[j] = tolower(dsc[j]);
  
  // remove all characters not matching the keyword set
  int dstptr = 0;
  for (string::size_type j = 0; j < dsc.length(); j++)
    {
      char c = dsc[j];
      if (isspace(c) || isalpha(c) || isdigit(c))
	dsc[dstptr++] = c;
    }
  dsc.resize(dstptr);
  
  // break the string into tokens
  Tokenizer t(dsc);
  vector<string> tokens;
  
  while (true)
    {
      string word = t.nextToken();
      if (word.length() == 0) // empty string means EOS
	break;
      else
	tokens.push_back(word);
    }
  
  return tokens;
}
