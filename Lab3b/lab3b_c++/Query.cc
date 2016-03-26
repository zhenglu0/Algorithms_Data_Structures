//
// QUERY.CC
// Describes a query operation on the event list
//

#include "Query.h"
#include "PrettyTime.h"

using namespace std;
  
// print method
ostream &operator<<(ostream &os, const Query &q)
{
    if (q.startTime != 0)
        os << "@"; PrettyTime::print(os, q.startTime) << " ";
  
    if (q.tos.size() == 1)
        os << q.from << " to " << q.tos[0] << "?";
    else
    {
        os << q.from << " to {" << q.tos[0];
      
        for (unsigned int j = 1; j < q.tos.size(); j++)
            os << ", " << q.tos[j];
      
        os << "}?";
    }
  
    return os;
}

