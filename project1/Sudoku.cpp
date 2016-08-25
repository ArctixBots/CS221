#include <iostream>
#include <sstream>
using namespace std;

#include "PuzzleState.hpp"
#include "Sudoku.hpp"

Sudoku::Sudoku(string config) {
  // I assume that the string 'config' is 81 characters long,
  // representing the initial configuration, // in row-major order.
  // Zeroes are for empty squares, and the
  // other digits are for squares already filled in.

  blankCount = 81;
  for (int i=0; i<9; i++) {
    for (int j=0; j<10; j++) {
      rowTally[i][j] = false;
      colTally[i][j] = false;
      zoneTally[i/3][i%3][j] = false;
    }
  }

  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (config[i*9+j]=='0') grid[i][j] = 0;
      else applyMove(i,j,config[i*9+j]-'0');
    }
  }
}

Sudoku::Sudoku(const Sudoku& other) {
  blankCount = other.blankCount;
  for (int i=0; i<9; i++) {
    for (int j=0; j<10; j++) {
      rowTally[i][j] = other.rowTally[i][j];
      colTally[i][j] = other.colTally[i][j];
      zoneTally[i/3][i%3][j] = other.zoneTally[i/3][i%3][j];
    }
  }

  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      grid[i][j] = other.grid[i][j];
    }
  }
}

Sudoku::~Sudoku() { }

void Sudoku::applyMove(int row, int col, int digit) {
  grid[row][col] = digit;
  blankCount--;
  rowTally[row][digit] = true;
  colTally[col][digit] = true;
  zoneTally[row/3][col/3][digit] = true;
}

bool Sudoku::isSolution() {
  // Since we make only legal moves, we've solved when all squares filled in.
  return blankCount==0;
}


vector<PuzzleState*> Sudoku::getSuccessors() {

  vector<PuzzleState*> result;

  // find a blank square to fill in
  int row = 0;
  int col = 0;
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (grid[i][j]==0) {
	row = i;
	col = j;
	goto foundOne;
      }
    }
  }
foundOne:

  for (int digit=1; digit<=9; digit++) {
    if (rowTally[row][digit]) continue; // digit already used in row
    if (colTally[col][digit]) continue; // digit already used in column
    if (zoneTally[row/3][col/3][digit]) continue; // digit already used in zone
    // This is a legal digit!  Add it to possible moves.
    Sudoku *temp = new Sudoku(*this);
    temp->applyMove(row,col,digit);
    result.push_back(temp);
  }

  return result;
}

int Sudoku::getBadness() {
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.

  // Not very useful for Sudoku

  return blankCount;
}

string Sudoku::getUniqId() {
  // This is a bit of a kludge, but it's easy.
  // We'll just use the print method to convert the PuzzleState
  // into a string representation.
  ostringstream temp;
  print(temp);
  return temp.str();
}

void Sudoku::print (ostream& out) {
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      out << " " << grid[i][j];
    }
    out << endl;
  }
}
