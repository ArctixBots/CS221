#ifndef _BAGOFPUZZLESTATES_HPP
#define _BAGOFPUZZLESTATES_HPP

#include "PuzzleState.hpp"

// BagOfPuzzleStates is a base class that provides an interface
// to an ADT that supports the operations: remove, add, and is_empty.
// Derived classes, such as ArrayStack and LinkedListQueue, determine
// the semantics of these operations. For example, LinkeListQueue
// implements add and remove to follow the First In First Out rule.
class BagOfPuzzleStates {
 public:
  // A destructor declared as virtual in the class declaration here
  // is given an implementation (the empty pair of { } curly braces)
  // so that deleting a BagOfPuzzleStates will invoke the destructor
  // of the derived class.
  inline virtual ~BagOfPuzzleStates() { }

  // The weird "=0" in "virtual void foo() =0;" is syntax that means
  // this function must be implemented by a derived class.

  // return the next PuzzleState, removing it from the bag
  virtual PuzzleState *take_out() = 0;

  // add a PuzzleState to the bag
  virtual void put_in(PuzzleState *element) = 0;

  // returns true if the bag is empty
  virtual bool is_empty() = 0;
};

#endif
