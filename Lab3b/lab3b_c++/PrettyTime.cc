//
// PRETTYTIME.CC
// Time printing routines
//

#include <iomanip>

#include "PrettyTime.h"

using namespace std;

//
// toTime()
// convert raw 24-hour time value to minutes since midnight.
//
int PrettyTime::toTime(int timeRaw)
{
    int hour   = (timeRaw / 100) % 24;
    int minute = timeRaw % 100;

    return hour * 60 + minute;
}
  
//
// print()
// Pretty-print a time.
// Input time is in minutes since midnight.
ostream &PrettyTime::print(ostream &os, int time)
{
    int hours = time / 60;
    int minutes = time % 60;

    os << std::setw(2) << std::setfill('0') << hours
     << ':'
     << std::setw(2) << std::setfill('0') << minutes;

    return os;
}

//
// elapsed()
// Compute elapsed time between two clock times
int PrettyTime::elapsed(int startTime, int endTime)
{
    int len = endTime - startTime;
    if (len < 0) len += 24 * 60; // next day

    return len;
}

//
// printElapsed()
// Pretty-print an elapsed time interval.
// Input times are in minutes since midnight.
ostream &PrettyTime::printElapsed(ostream &os, int startTime, int endTime)
{
    int len = elapsed(startTime, endTime);

    int hours   = len / 60;
    int minutes = len % 60;

    if (hours > 0)
    os << hours << " hours";

    if (hours > 0 && minutes > 0)
    os << " and ";

    if (minutes > 0)
    os << minutes << " minutes";

    return os;
}
