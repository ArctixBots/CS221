#ifndef _WOLFGOATCABBAGE_HPP
#define _WOLFGOATCABBAGE_HPP

#include <iostream>
using namespace std;

/*
  WolfGoatCabbage.hpp

  Classic problem (from the middle ages) of crossing a river
  with a wolf, goat, and cabbage.
*/

class WolfGoatCabbage : public PuzzleState {
 public:
  WolfGoatCabbage();
  WolfGoatCabbage(int, int, int, int);
  ~WolfGoatCabbage();

  // returns true if this PuzzleState is a solution for the puzzle
  bool isSolution();

  // returns a vector of possible next positions for the puzzle.
  vector<PuzzleState*> getSuccessors();

  // If you want to use BestFS, you must assign a priority value to
  // all puzzle states.  (If you don't want to use BestFS, you
  // can just return 0 for all PuzzleStates.)
  //
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.
  int getBadness();

  // For many dictionary implementations, it's convenient to have
  // a unique ID for each state (so we can sort them,
  // hash them, etc.)
  //
  // Returns a unique string for any state
  string getUniqId();

  // print the puzzle state
  void print (ostream& out);
 private:
  // This is a low-level, quick-and-dirty implementation.
  int boat; // position of human and boat: 0 means before; 1 means across
  int wolf; // position of wolf
  int goat; // position of goat
  int cabbage; // position of cabbage
};

#endif
