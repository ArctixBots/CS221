//StdStack.hpp
#ifndef _STDSTACK_HPP
#define _STDSTACK_HPP

#include <stack>
#include "BagOfPuzzleStates.hpp"

// This is an adapter class to use the C++ Standard Library Deque
// data structure to give us a working stack as a BagOfPuzzleStates.
class StdStack: public BagOfPuzzleStates
{
 public:
  StdStack(); // constructor
  
  // BagOfPuzzleStates interface
  void put_in(PuzzleState *elem);
  PuzzleState *take_out();
  bool is_empty();

  ~StdStack(); // destructor

 private:
  // This declares a stack from the C++ standard library,
  // whose elements are of type (PuzzleState *)
  std::stack<PuzzleState *> bag;
};

#endif
