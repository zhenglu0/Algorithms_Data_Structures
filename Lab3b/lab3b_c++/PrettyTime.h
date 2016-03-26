//
// PRETTYTIME.H
// Time printing routines
//

#ifndef __PRETTYTIME_H
#define __PRETTYTIME_H

#include <iostream>

class PrettyTime {
    
public:
    //
    // toTime()
    // convert raw 24-hour time value to minutes since midnight.
    //
    static int toTime(int timeRaw);

    //
    // print()
    // Pretty-print a time.
    // Input time is in minutes since midnight.
    static std::ostream &print(std::ostream &os, int time);

    //
    // elapsed()
    // Compute elapsed time between two clock times
    static int elapsed(int startTime, int endTime);

    //
    // printElapsed()
    // Pretty-print an elapsed time interval.
    // Input times are in minutes since midnight.
    static std::ostream &printElapsed(std::ostream &os, int startTime, int endTime);
    
};

#endif
