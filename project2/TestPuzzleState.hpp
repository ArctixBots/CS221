#ifndef _TESTPUZZLESTATE_HPP
#define _TESTPUZZLESTATE_HPP

#include <iostream>
#include <string>
using namespace std;

/*
  TestPuzzleState.hpp

  Popular puzzle where you slide tiles around a board, e.g.,
  the "15 Puzzle", the "8 Puzzle", etc.
*/

class TestPuzzleState : public PuzzleState {
 public:
  TestPuzzleState(string, int, bool);
  TestPuzzleState(const TestPuzzleState&); // Deep copy constructor
  ~TestPuzzleState();

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
  string getUniqId(void);

  // print the puzzle state
  void print (ostream& out);
 private:
  string uniqId;
  int badness;
  bool solution;
};

#endif
