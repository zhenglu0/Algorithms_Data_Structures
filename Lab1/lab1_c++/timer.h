//
// TIMER.H
// A simple CPU timer
//
#ifndef __TIMER_H
#define __TIMER_H

class Timer {
public:
  Timer(void) {}
  
  void start(void); // start the timer
  void stop(void);  // stop the timer
  
  // Return the elapsed time (in milliseconds) between the last
  // pair of start() and stop() calls.
  //
  double elapsedTime(void) const { return 1000.0 * _elapsedTime; }
  
private:
  double _elapsedTime;
  double _startTime;
};

#endif
