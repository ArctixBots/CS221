#ifndef _KLICKETY_HPP
#define _KLICKETY_HPP

#include <iostream>
#include <string>
using namespace std;

/*
  Marble.hpp

  Jump marble X over an adjacent (horizontally or vertically) marble Y
  and remove marble Y.  You win if you remove all but one marble.
*/

class Marble : public PuzzleState {
 public:
  Marble(int, int, string);
  Marble(const Marble&); // Deep copy constructor
  ~Marble();

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
  const int rows; // number of rows
  const int cols; // number of columns
  string board; // array of rows*cols characters to hold the board
  int marbs; // number of marbles on board
  Marble* jumpMarble( int r, int c, int dr, int dc );
};

#endif
