//
// TOKENIZER.H
// Given a string, break it into whitespace-delimited tokens.
// Return successive tokens on each nextToken() call.
//

#ifndef __TOKENIZER_H
#define __TOKENIZER_H

#include <string>

class Tokenizer {
  
private: 
  const std::string &s;
  unsigned int posn;
  
public:		 
  Tokenizer(const std::string &is);
  
  std::string nextToken();
  
  std::string rest() const;
};

#endif
