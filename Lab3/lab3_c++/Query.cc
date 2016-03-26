//
// QUERY.CC
// Describes a query operation on the event list
//

#include "Query.h"

std::ostream &operator<<(std::ostream &os, const Query &q)
{
  switch (q.command)
    {
    case Query::FINDRANGE:
      os << "FINDRANGE " << q.year1 << ' ' << q.year2;
      break;
      
    case Query::FINDMOSTRECENT:
      os << "FINDMOSTRECENT " << q.year1;
      break;
      
    case Query::FINDKEYWORD:
      os << "FINDKEYWORD " << q.keyword;
      break;
      
    case Query::DELETE:
      os << "DELETE " << q.year1;
      break;
    }
  
  return os;
}
