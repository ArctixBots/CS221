/*
  solve.cpp: contains 'main' function.

*/

#include <iostream>

#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <unistd.h>

// 221 STUDENTS: You'll need to include any .hpp files of classes that
// you create and use here
#include "PuzzleState.hpp"
#include "WolfGoatCabbage.hpp"
#include "SliderPuzzle.hpp"
#include "Sudoku.hpp"
#include "MazeRunner.hpp"
#include "Marble.hpp"
#include "TestPuzzleState.hpp"

// 221 STUDENTS:  These are simple stack and queue implementations
// using the C++ standard library data structures.
// This guarantees you'll have working code, instead of using
// stacks and queues you implemented in Project 1.
#include "StdStack.hpp"
#include "StdQueue.hpp"
// 221 STUDENTS:  This is something you'll have to write.
#include "HeapPriorityQueue.hpp"

// 221 STUDENTS:  This is an optimized version of the LinkedListDict in Proj 1
#include "LinkedListDict.hpp"
// 221 STUDENTS:  And these are classes you'll have to write.
#include "FixedChainHashDict.hpp"
#include "ResizeChainHashDict.hpp"

using namespace std;


// This function does the actual solving.
void solvePuzzle(PuzzleState *start, BagOfPuzzleStates &active, PredDict &seen, vector<PuzzleState*> &solution) {
  PuzzleState *state;
  PuzzleState *temp;

  active.put_in(start); // Must explore the successors of the start state.
  seen.add(start,NULL); // We've seen this state.  It has no predecessor.

int foo=0;
  while (!active.is_empty()) {
    // Loop Invariants:
    // 'seen' contains the set of puzzle states that we know how to reach.
    // 'active' contains the set of puzzle states that we know how to reach,
    //    and whose successors we might not have explored yet.

foo++;
if (foo % 1000 == 0) cout << foo << endl;

    state = active.take_out();
    // Note:  Do not delete this, as this PuzzleState is also in 'seen'

    // The following two lines are handy for debugging, or seeing what
    // the algorithm is doing.
    // 221 STUDENTS:  Comment these out when you want the program to
    // run at full speed!
    //cout << "Exploring State: \n";
    //state->print(cout);
    //usleep(100000);	// Pause for some microseconds, to let human read output

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


int tests() {
  PuzzleState * a = new TestPuzzleState("a", 10, false);
  PuzzleState * b = new TestPuzzleState("b", 15, false);
  PuzzleState * c = new TestPuzzleState("c", 20, false);
  PuzzleState * d = new TestPuzzleState("d", 25, false);
  PuzzleState * e = new TestPuzzleState("e", 30, false);
  std::vector<PuzzleState *> states;

  cout << "Running tests!" << endl;

  cout << "HeapPriorityQueue" << endl;
  HeapPriorityQueue q;
  assert(q.is_empty());
  q.put_in(e);
  q.put_in(c);
  q.put_in(a);
  q.put_in(b);
  q.put_in(d);
  for (int i=40; i < 100; i++) {
    PuzzleState * n = new TestPuzzleState("meh", i, false);
    states.push_back(n);
    q.put_in(n);
  }
  assert(q.take_out() == a);
  assert(!q.is_empty());
  assert(q.take_out() == b);
  assert(q.take_out() == c);
  assert(q.take_out() == d);
  assert(q.take_out() == e);
  for (int i=0; i < int(states.size()); i++) {
    assert(q.take_out() == states[i]);
  }
  assert(q.is_empty());

  cout << "FixedChainHashDict" << endl;
  states.clear();
  FixedChainHashDict h(1000);
  h.add(a, a);
  h.add(b, b);
  h.add(c, c);
  for (int i=0; i < 100000; i++) {
    stringstream ss;
    ss << "meh" << i;
    PuzzleState * n = new TestPuzzleState(ss.str(), i, false);
    states.push_back(n);
    h.add(n, n);
  }
  PuzzleState * resp;
  assert(h.find(a, resp));
  assert(resp == a);
  assert(h.find(b, resp));
  assert(resp == b);
  assert(h.find(c, resp));
  assert(resp == c);
  for (int i=0; i < int(states.size()); i++) {
    PuzzleState * n = states[i];
    assert(h.find(n, resp));
    assert(resp == n);
  }


  a = new TestPuzzleState("a", 10, false);
  b = new TestPuzzleState("b", 15, false);
  c = new TestPuzzleState("c", 20, false);

  cout << "ResizeChainHashDict" << endl;
  states.clear();
  ResizeChainHashDict hr;
  hr.add(a, a);
  hr.add(b, b);
  hr.add(c, c);
  for (int i=0; i < 1000000; i++) {
    stringstream ss;
    ss << "meh" << i;
    PuzzleState * n = new TestPuzzleState(ss.str(), i, false);
    states.push_back(n);
    hr.add(n, n);
  }
  hr.find(a, resp);
  assert(resp == a);
  hr.find(b, resp);
  assert(resp == b);
  hr.find(c, resp);
  assert(resp == c);
  for (int i=0; i < int(states.size()); i++) {
    PuzzleState * n = states[i];
    assert(hr.find(n, resp));
    assert(resp == n);
  }

  return 0;
}

int main () {
  // return tests();

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
  //startState = new Marble(7,7,"  ooo   ooooo oooooooooo.oooooooooo ooooo   ooo  ");

  //startState = new SliderPuzzle(3,3,"8 7 6 5 4 3 2 1 0");
  //startState = new SliderPuzzle(3,4,"11 10 9 8 7 6 5 4 3 1 2 0");
  //startState = new SliderPuzzle(4,4,"15 14 13 12 11 10 9 8 7 6 5 4 3 1 2 0");
  startState = new SliderPuzzle(5,5,"24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0");


  // 221 STUDENTS:  Uncomment one of these, to select BFS, DFS, or BestFS.
  //StdQueue activeStates;
  //StdStack activeStates;
  HeapPriorityQueue activeStates;

  // Eventually, we'll replace this with a better dictionary ADT...
  //LinkedListDict seenStates;
  //FixedChainHashDict seenStates(1000);
  ResizeChainHashDict seenStates;

  vector<PuzzleState*> solution;

  solvePuzzle(startState, activeStates, seenStates, solution);

  // Print out solution
  for (int i=(int)solution.size()-1; i >= 0; i--) {
    cout << "STEP " << solution.size()-i << ":\n";
    solution[i]->print(cout);
    cout << endl;
  }

  // NO!!!  The destructor for seenStates will delete all generated
  // PuzzleStates exactly once!
  // delete startState;

  return 0;
}
