//StdQueue.hpp
#ifndef _STDQUEUE_HPP
#define _STDQUEUE_HPP

#include <queue>
#include "BagOfPuzzleStates.hpp"

// This is an adapter class to use the C++ Standard Library Deque
// data structure to give us a working queue as a BagOfPuzzleStates.
class StdQueue: public BagOfPuzzleStates
{
 public:
  StdQueue(); // constructor
  
  // BagOfPuzzleStates interface
  void put_in(PuzzleState *elem);
  PuzzleState *take_out();
  bool is_empty();

  ~StdQueue(); // destructor

 private:
  // This declares a queue from the C++ standard library,
  // whose elements are of type (PuzzleState *)
  std::queue<PuzzleState *> bag;
};

#endif
