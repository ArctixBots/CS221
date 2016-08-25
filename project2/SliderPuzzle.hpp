#ifndef _SLIDERPUZZLE_HPP
#define _SLIDERPUZZLE_HPP

#include <iostream>
#include <string>
using namespace std;

/*
  SliderPuzzle.hpp

  Popular puzzle where you slide tiles around a board, e.g.,
  the "15 Puzzle", the "8 Puzzle", etc.
*/

class SliderPuzzle : public PuzzleState {
 public:
  SliderPuzzle(int, int, string);
  SliderPuzzle(const SliderPuzzle&); // Deep copy constructor
  ~SliderPuzzle();

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
  int *board; // array of size rows*cols to hold the board
  int empty_row; // row of the empty space
  int empty_col; // col of the empty space
  void slide_down(); // slide a tile down into empty space
  void slide_up(); // slide a tile up into empty space
  void slide_right(); // slide a tile right into empty space
  void slide_left(); // slide a tile left into empty space
};

#endif
