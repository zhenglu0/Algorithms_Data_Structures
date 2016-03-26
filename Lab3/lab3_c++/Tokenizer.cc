//
// TOKENIZER.CC
// Given a string, break it into whitespace-delimited tokens.
// Return successive tokens on each nextToken() call.
//

#include "Tokenizer.h"

#include <cctype>

using namespace std;


Tokenizer::Tokenizer(const std::string &is)
  : s(is), posn(0)
{}
    
// return the next token, or an empty string if no tokens remain
string Tokenizer::nextToken()
{
  unsigned int start = posn;
	
  // skip leading whitespace
  while (start < s.length() && isspace(s[start]))
    start++;
	
  // move fwd to next whitespce character
  unsigned int end = start;
  while (end < s.length() && !isspace(s[end]))
    end++;
	
  posn = end;
  return s.substr(start, end - start);
}

// return untokenized suffix of string
string Tokenizer::rest() const
{
  return s.substr(posn);
}
