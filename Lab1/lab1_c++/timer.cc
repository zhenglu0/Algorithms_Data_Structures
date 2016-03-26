//
// TIMER.CC
// A simple CPU timer.  This class essentially just wraps the UNIX
// getrusage() function, returning total *user* CPU time.  For Windows,
// I'm sure there's an equivalent to getrusage() that you could use
// instead.
//
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

#include "timer.h"

void Timer::start(void)
{
  struct rusage usage;
  
  getrusage(RUSAGE_SELF, &usage);
  
  _startTime = 
    double(usage.ru_utime.tv_sec) + 1.0e-6 * double(usage.ru_utime.tv_usec);
}


void Timer::stop(void)
{
  struct rusage usage;
  
  getrusage(RUSAGE_SELF, &usage);
  
  double endTime =
    double(usage.ru_utime.tv_sec) + 1.0e-6 * double(usage.ru_utime.tv_usec);
  
  _elapsedTime = endTime - _startTime;
  
  if (_elapsedTime < 0.0) // unfortunately, timer can be nonmonotonic
    _elapsedTime = 0.0;
} 
