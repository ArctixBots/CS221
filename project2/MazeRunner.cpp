#include <iostream>
#include <sstream>
//#include <cmath>
#include <cstdlib>

using namespace std;

#include "PuzzleState.hpp"
#include "MazeRunner.hpp"


MazeRunner::MazeRunner(int r, int c, string config, int startr, int startc) :
  rows(r), cols(c) {
    // The constructor takes the number of rows and columns in the maze,
    // then a string of length row*col showing the maze, in row-major order,
    // where a space indicates open space, $ indicates a target, and
    // other characters indicate obstacles.
    // The last two parameters are the starting row and column.
  int i, j;

  maze = new char[rows*cols];
  target_row = -1;	// Default values in case no target given.
  target_col = -1;
  for (i=0; i<rows; i++) {
    for (j=0; j<cols; j++) {
      maze[i*cols+j] = config[i*cols+j];
      if (maze[i*cols+j]=='$') {
        // Store location of a target for badness computation.
	target_row = i;
	target_col = j;
      }
    }
  }
  my_row = startr;
  my_col = startc;
}

MazeRunner::MazeRunner(const MazeRunner& other) : rows(other.rows), cols(other.cols) {
  maze = new char[rows*cols];
  for (int i=0; i<rows*cols; i++) {
    maze[i] = other.maze[i];
  }
  my_row = other.my_row;
  my_col = other.my_col;
  target_row = other.target_row;
  target_col = other.target_col;
}

MazeRunner::~MazeRunner() { delete [] maze; }

bool MazeRunner::isSolution() {
  // We've found a target if the maze at the current position is a $
  return maze[my_row*cols+my_col] == '$';
}



void MazeRunner::move_down() {
  my_row++;
}

void MazeRunner::move_up() {
  my_row--;
}

void MazeRunner::move_right() {
  my_col++;
}

void MazeRunner::move_left() {
  my_col--;
}


vector<PuzzleState*> MazeRunner::getSuccessors() {

  vector<PuzzleState*> result;

  // Can I move down?
  if ((my_row!=rows-1) && ((maze[(my_row+1)*cols+my_col]==' ') ||
        (maze[(my_row+1)*cols+my_col]=='$'))
     ) {
    MazeRunner* temp = new MazeRunner(*this);
    temp->move_down();
    // Add it to the results
    result.push_back(temp);
  }
  // Can I move up?
  if ((my_row!=0) && ((maze[(my_row-1)*cols+my_col]==' ') ||
        (maze[(my_row-1)*cols+my_col]=='$'))
     ) {
    MazeRunner* temp = new MazeRunner(*this);
    temp->move_up();
    // Add it to the results
    result.push_back(temp);
  }
  // Can I move right?
  if ((my_col!=cols-1) && ((maze[my_row*cols+my_col+1]==' ') ||
        (maze[my_row*cols+my_col+1]=='$'))
     ) {
    MazeRunner* temp = new MazeRunner(*this);
    temp->move_right();
    // Add it to the results
    result.push_back(temp);
  }
  // Can I move left?
  if ((my_col!=0) && ((maze[my_row*cols+my_col-1]==' ') ||
        (maze[my_row*cols+my_col-1]=='$'))
     ) {
    MazeRunner* temp = new MazeRunner(*this);
    temp->move_left();
    // Add it to the results
    result.push_back(temp);
  }

  return result;
}

int MazeRunner::getBadness() {
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.

  return abs(target_row-my_row) + abs(target_col-my_col);
}

string MazeRunner::getUniqId() {
  // The maze state doesn't change, so state is unqiuely determined
  // by my_row and my_col.  This maps these into a string.
  // This is a bit of a kludge...
  ostringstream temp;
  temp << my_row << "," << my_col;
  return temp.str();
}

void MazeRunner::print (ostream& out) {
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      if ((i==my_row) && (j==my_col)) out << '@';
      else out << maze[i*cols+j];
    }
    out << endl;
  }
}
