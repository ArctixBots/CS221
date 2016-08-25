/*
  solve.cpp: contains 'main' function.

*/

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <unistd.h>

// 221 STUDENTS: You'll need to include any .hpp files of classes that
// you create and use here
#include "PuzzleState.hpp"
#include "WolfGoatCabbage.hpp"
#include "SliderPuzzle.hpp"
#include "Sudoku.hpp"
#include "MazeRunner.hpp"
#include "Marble.hpp"

#include "ArrayStack.hpp"
#include "LinkedListStack.hpp"
// 221 STUDENTS:  These are the ones you'll have to write.
#include "LinkedListQueue.hpp"
#include "ArrayQueue.hpp"

#include "LinkedListDict.hpp"

using namespace std;


// This function does the actual solving.
void solvePuzzle(PuzzleState *start, BagOfPuzzleStates &active, PredDict &seen, vector<PuzzleState*> &solution) {
  PuzzleState *state;
  PuzzleState *temp;

  active.put_in(start); // Must explore the successors of the start state.
  seen.add(start,NULL); // We've seen this state.  It has no predecessor.

  while (!active.is_empty()) {
    // Loop Invariants:
    // 'seen' contains the set of puzzle states that we know how to reach.
    // 'active' contains the set of puzzle states that we know how to reach,
    //    and whose successors we might not have explored yet.

    state = active.take_out();
    // Note:  Do not delete this, as this PuzzleState is also in 'seen'

    // The following two lines are handy for debugging, or seeing what
    // the algorithm is doing.
    // 221 STUDENTS:  Comment these out when you want the program to
    // run at full speed!
    //cout << "Exploring State: \n";
    //state->print(cout);
    //usleep(10000);	// Pause for some microseconds, to let human read output

    if (state->isSolution()) {
      // Found a solution!
      cout << "Found solution! \n";
      state->print(cout);

      // Follow predecessors to construct path to solution.
      temp = state;
      while (temp!=NULL) {
	solution.push_back(temp);
	// Guaranteed to succeed, because these states must have been
	// added to dictionary already.
        seen.find(temp,temp);
      }
      return;
    }

    vector<PuzzleState*> nextMoves = state->getSuccessors();
    for (unsigned int i=0; i < nextMoves.size(); i++) {
      if (!seen.find(nextMoves[i], temp)) {
        // Never seen this state before.  Add it to 'seen' and 'active'
        active.put_in(nextMoves[i]);
        seen.add(nextMoves[i], state);
      } else {
	delete nextMoves[i];
      }
    }
  }

  // Ran out of states to explore.  No solution!
  solution.clear();
  return;
}

int main ()
{
  PuzzleState *startState;

  // 221 STUDENTS: Initialize startState with an object of the type
  // of puzzle you want solved.
  // For some kinds of puzzles, you will want to pass in a parameter
  // to specify the starting position (e.g., for the 8- or 15-puzzles.)

  // This is for the WolfGoatCabbage problem.
  //startState = new WolfGoatCabbage();

  //startState = new MazeRunner(21,41, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                                       XX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX XX                                     X XX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X XX                                   X X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X X XX                                   X X XX X X X X X XXXXXXXXXXXXXXXXXXXXXXXXX X XX X X X X X X                         X XX X X X X XXX XXXXXXXXXXXXXXXXXXXXXXX X XX X X X X X X           X$            X XX X X X XXX XXXXXXXXXXXXXXXXXXXXXXXXXXX XX X X X X X X                         X XX X X XXX X X XXXXXXXXXXXXXXXXXXXXXXX X XX X X X X X X X                       X XX X XXX X X X XXXXXXXXXXXXXXXXXXXXXXXXX XX X X                                   XX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                                       X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",1,1);
// This is what the maze looks like...
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// X                                       X
// X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X
// X                                     X X
// X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X X
// X                                   X X X
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X X X
// X                                   X X X
// X X X X X X XXXXXXXXXXXXXXXXXXXXXXXXX X X
// X X X X X X X                         X X
// X X X X X XXX XXXXXXXXXXXXXXXXXXXXXXX X X
// X X X X X X X           X$            X X
// X X X X XXX XXXXXXXXXXXXXXXXXXXXXXXXXXX X
// X X X X X X X                         X X
// X X X XXX X X XXXXXXXXXXXXXXXXXXXXXXX X X
// X X X X X X X X                       X X
// X X XXX X X X XXXXXXXXXXXXXXXXXXXXXXXXX X
// X X X                                   X
// X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// X                                       X
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

  // This is an empty Sudoku grid:
  //startState = new Sudoku("000000000000000000000000000000000000000000000000000000000000000000000000000000000");

  // This is a medium difficulty problem:
  //  startState = new Sudoku("167000000050600047000300009641057000800060005000980716700008000490006050000000671");

  // And this next one is a really easy Sudoku...
  //startState = new Sudoku("927430008060000097008000402000308005400060003800201000602000300790000080500089271");

  // English peg solitaire
  //startState = new Marble(7,7,"  ooo    ooo  oooooooooo.oooooooooo  ooo    ooo  ");
  // European peg solitaire
  //  startState = new Marble(7,7,"  ooo   ooooo oooooooooo.oooooooooo ooooo   ooo  ");

  startState = new SliderPuzzle(3,3,"8 7 6 5 4 3 2 1 0");
  //startState = new SliderPuzzle(3,4,"11 10 9 8 7 6 5 4 3 1 2 0");
  //startState = new SliderPuzzle(4,4,"15 14 13 12 11 10 9 8 7 6 5 4 3 1 2 0");


  // 221 STUDENTS:  Uncomment one of these, to select BFS or DFS.
  // Later, you will put declarations here to use your new implementations
  // (ArrayQueue, or LinkedListQueue).
  ArrayStack activeStates;
  //LinkedListStack activeStates;
  //ArrayQueue activeStates;
  //LinkedListQueue activeStates;

  // Eventually, we'll replace this with a better dictionary ADT...
  LinkedListDict seenStates;

  vector<PuzzleState*> solution;

  solvePuzzle(startState, activeStates, seenStates, solution);

  // Print out solution
  for (int i=(int)solution.size()-1; i >= 0; i--) {
    cout << "STEP " << solution.size()-i << ":\n";
    solution[i]->print(cout);
    cout << endl;
  }

  delete startState;

  return 0;
}
