#ifndef _PREDDICT_HPP
#define _PREDDICT_HPP

#include "PuzzleState.hpp"

// PredDict is a base class that provides an interface to an ADT that
// supports the operations: add(key,pred) and find(key).  A
// PredDict stores (a pointer to) the predecessor state of each
// (pointer to) a PuzzleState in the dictionary (i.e., a state that
// leads to the PuzzleState).

// We use this both to keep track of whether we've
// explored a state before (so we don't duplicate work
// or get stuck in cycles), as well as to generate the
// sequence of states leading to a puzzle solution, if
// that's desired.

// Different implementations will have different efficiency.

class PredDict {
 public:
  // A destructor declared as virtual is given an implementation
  // (in this case, the empty curly braces { } ) so that deleting a
  // PredDict will invoke the destructor of the derived class.
  virtual ~PredDict() { }

  // Returns true iff the key is found.
  //
  // If the key is found, pred is set to the predecessor.
  //
  // Note:  Do not delete the object pointed to by key or pred,
  //        since the dictionary stores pointers to these objects.
  virtual bool find(PuzzleState *key, PuzzleState *&pred) = 0;

  // add a (key, predecessor) pair to the dictionary
  //
  // Note:  Do not delete the object pointed to by key or pred,
  //        since the dictionary stores pointers to these objects.
  virtual void add(PuzzleState *key, PuzzleState *pred) = 0;
};

#endif
