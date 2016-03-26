#ifndef __RECORD_H
#define __RECORD_H

#include <vector>

class Record {
public:
    const char *key;
    std::vector<int> positions;
    int toHashValue;
    Record(const char *s)
    {
        key = s;
    }
};

#endif
