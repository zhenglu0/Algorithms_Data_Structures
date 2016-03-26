//
// QUERY.H
// Describes a query operation on the event list
//

#ifndef __QUERY_H
#define __QUERY_H

#include <iostream>
#include <string>
#include <vector>

struct Query {
    int startTime;
    std::string from;
    std::vector<std::string> tos;
};

std::ostream &operator<<(std::ostream &os, const Query &q);

#endif
