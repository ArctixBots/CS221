#include "Timer.h"

#include <cassert>
#include <chrono>

typedef std::chrono::high_resolution_clock hr_clock;

// precondition: not paused
hr_clock::time_point Timer::internalPause() {
  assert(!paused);

  timePaused = hr_clock::now();
  paused = true;
  
  return timePaused;
}

hr_clock::time_point Timer::internalResume() {
  assert(paused);
  paused = false;
  
  hr_clock::time_point timeResumed = hr_clock::now();
  timeBefore += timeResumed - timePaused;
  
  return timeResumed;
}

void Timer::internalTimestamp(std::ostream & out, uint64_t count, 
			      hr_clock::time_point timeNow) {
  out << count << " " << (timeNow - timeBefore).count() << std::endl;
}

Timer::Timer() {
  reset();
}

void Timer::reset() {
  timeBefore = hr_clock::now();
  paused = false;
}

// precondition: not paused.
void Timer::pause() {
  internalPause();
}

// precondition: paused.
void Timer::resume() {
  internalResume();
}

// precondition: not paused
void Timer::timestamp_and_pause(std::ostream & out, uint64_t count) {
  assert(!paused);
  internalTimestamp(out, count, internalPause());
}

// precondition: paused
void Timer::timestamp_and_resume(std::ostream & out, uint64_t count) {
  assert(paused);
  internalTimestamp(out, count, timePaused);
}

// precondition: not paused
void Timer::timestamp(std::ostream & out, uint64_t count) {
  assert(!paused);
  internalTimestamp(out, count, internalPause());
  internalResume();
}

hr_clock::duration Timer::timeSoFar() {
  bool wasPaused = paused;
  if (!wasPaused) 
    internalPause();
  hr_clock::duration result = timePaused - timeBefore;
  if (!wasPaused)
    internalResume();
  return result;
}

