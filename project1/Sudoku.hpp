#ifndef _SUDOKU_HPP
#define _SUDOKU_HPP

#include <iostream>
#include <string>
using namespace std;

/*
  Sudoku.hpp

  Everyone knows Sudoku!
*/

class Sudoku : public PuzzleState {
 public:
  Sudoku(string);
  Sudoku(const Sudoku&); // Deep copy constructor
  ~Sudoku();

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
  int grid[9][9]; // array to hold the grid, 0 for blanks
  // Below are helper fields, that make the code more efficient
  // and easier to write.
  // It's important to maintain class invariants (like loop invariants)
  // that all methods maintain these variables with accurate values.
  int blankCount; // how many blank spaces left
  bool rowTally[9][10]; // for each row, have we used a given digit yet?
  bool colTally[9][10]; // similar, for each column
  bool zoneTally[3][3][10]; // similar, for each zone
  void applyMove(int row, int col, int digit); // Writes a digit into the grid
};

#endif
