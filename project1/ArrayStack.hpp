//ArrayStack.hpp
#ifndef _ARRAYSTACK_HPP
#define _ARRAYSTACK_HPP

#include "BagOfPuzzleStates.hpp"

// 221 STUDENTS:
//
// This skeleton file (along with the .cpp) is here to help get you
// started, but you are free to change function signatures, etc. as
// long as ArrayStack is derived from (i.e., is a subclass of)
// BagOfPuzzleStates.
class ArrayStack: public BagOfPuzzleStates
{
public:
  ArrayStack(); // constructor - DO NOT CHANGE SIGNATURE!
  
  // BagOfPuzzleStates interface
  void put_in(PuzzleState *elem);
  PuzzleState *take_out();
  bool is_empty();

  ~ArrayStack(); // destructor

  static const int INIT_SIZE = 5;

private:
  // A helper function that consumes a number and ensures the queue
  // has enough space for that many elements.
  void ensure_capacity(int n);

  // a pointer to the underlying array with elements of (PuzzleState *)
  PuzzleState **array;

  // the index of the element currently the top element of the ArrayStack
  int top;

  // how many elements the stack is capable of holding in the underlying array
  int capacity;
};

#endif
