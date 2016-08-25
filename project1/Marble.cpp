#include <iostream>
#include <sstream>
//#include <cmath>
#include <cstdlib> // for abs
using namespace std;

#include "PuzzleState.hpp"
#include "Marble.hpp"

Marble::Marble(int r, int c, string config) : rows(r), cols(c) {
  int i, j;

  // I assume that 'config' is a string of r*c characters:
  // ' ' represents outside the puzzle,
  // 'o' represents a marble,
  // '.' represents a hole.
  board = config;
  marbs = 0;
  for (i=0; i<rows; i++) {
    for (j=0; j<cols; j++) {
      if( board[i*cols+j] == 'o' ) marbs++;
    }
  }
}

Marble::Marble(const Marble& other) : rows(other.rows), cols(other.cols), board(other.board), marbs(other.marbs) {
}

Marble::~Marble() { }

bool Marble::isSolution() {
  return marbs <= 1;
}

Marble* Marble::jumpMarble( int r, int c, int dr, int dc ) {
  int rr = r + dr;
  int rrr = rr + dr;
  int cc = c + dc;
  int ccc = cc + dc;
  if( ccc < 0 || ccc >= cols || rrr < 0 || rrr >= rows )
    return NULL;
  if( board[rrr*cols + ccc] != '.' || board[rr*cols + cc] != 'o' )
    return NULL;
  Marble* temp = new Marble(*this);
  temp->board[r*cols + c] = '.';
  temp->board[rr*cols + cc] = '.';
  temp->board[rrr*cols + ccc] = 'o';
  temp->marbs--;
  return temp;
}

vector<PuzzleState*> Marble::getSuccessors() {
  vector<PuzzleState*> result;
  Marble* temp;
  for( int r=0; r<rows; r++ ) {
    for( int c=0; c<cols; c++ ) {
      // look for a marble that can jump over another
      if( board[r*rows + c] == 'o' ) {
	if( (temp = jumpMarble(r, c, +1, 0)) ) result.push_back(temp);
	if( (temp = jumpMarble(r, c, -1, 0)) ) result.push_back(temp);
	if( (temp = jumpMarble(r, c, 0, +1)) ) result.push_back(temp);
	if( (temp = jumpMarble(r, c, 0, -1)) ) result.push_back(temp);
      }
    }
  }
  return result;
}

int Marble::getBadness() {
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.

  return marbs;
}

string Marble::getUniqId() {
  return board;
}

void Marble::print (ostream& out) {
  for (int r=0; r<rows; r++) {
    for (int c=0; c<cols; c++) {
      out << board[r*cols+c];
    }
    out << endl;
  }
}
