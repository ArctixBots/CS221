#ifndef __TIMER_H
#define __TIMER_H

#include <sys/times.h>
#include <ostream>
#include <chrono>

// Time operations, with the option of outputting a timestamp to a
// stream with minimal interruption to timing.
class Timer {
  std::chrono::high_resolution_clock::time_point timeBefore;
  std::chrono::high_resolution_clock::time_point timePaused;
  bool paused;

  std::chrono::high_resolution_clock::time_point internalPause();
  std::chrono::high_resolution_clock::time_point internalResume();
  void internalTimestamp(std::ostream & out, uint64_t count, 
			 std::chrono::high_resolution_clock::time_point timeNow);

public:
  typedef std::chrono::high_resolution_clock::duration duration;
  Timer();
  void reset();
  void pause();  //precondition: not paused
  void resume();  //precondition: paused
  void timestamp_and_pause(std::ostream & out, uint64_t count);  //precondition: not paused
  void timestamp_and_resume(std::ostream & out, uint64_t count); //precondition: paused
  void timestamp(std::ostream & out, uint64_t count); //precondition: not paused
  duration timeSoFar();
};

#endif // __TIMER_H
