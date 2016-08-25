#ifndef _PUZZLESTATE_HPP
#define _PUZZLESTATE_HPP

#include <iostream>
#include <vector>
using namespace std;

/*
  PuzzleState.hpp
  Defines the abstract class PuzzleState

*/

class PuzzleState {
 public:
  // virtual destructor, since we have virtual methods
  virtual ~PuzzleState() { }

  // returns true if this PuzzleState is a solution for the puzzle
  virtual bool isSolution() = 0;

  // returns a vector of possible next positions for the puzzle.
  virtual vector<PuzzleState *> getSuccessors(void) = 0;

  // If you want to use BestFS, you must assign a priority value to
  // all puzzle states.  (If you don't want to use BestFS, you
  // can just return a constant for all PuzzleStates.)
  //
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.
  virtual int getBadness(void) = 0;

  // For many dictionary implementations, it's convenient to have
  // a unique numerical ID for each state (so we can sort them,
  // hash them, etc.)
  //
  // Returns a unique integer for any state
  virtual string getUniqId(void) = 0;

  // print the puzzle state
  virtual void print (ostream& out) = 0;

  // For many purposes (e.g., a Dictionary ADT as a BST), it's
  // convenient to have a total order on PuzzleStates.
  // These declarations give comparison operations for this order.
  // Note that we cannot use getBadness as this order, because there
  // can be many states with the same badness.
  friend bool operator<=(PuzzleState &a, PuzzleState &b);
};

#endif
