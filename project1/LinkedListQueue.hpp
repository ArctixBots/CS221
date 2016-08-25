//LinkedListQueue.hpp
#ifndef _LINKEDLISTQUEUE_HPP
#define _LINKEDLISTQUEUE_HPP

#include "PuzzleState.hpp"
#include "BagOfPuzzleStates.hpp"

// This skeleton file (along with the .cpp) is
// here to help get you started, but you are
// free to change function signatures, etc.
// as long as LinkedListQueue is some subtype
// of BagOfPuzzleStates

class LinkedListQueue: public BagOfPuzzleStates
{
 public:
  LinkedListQueue();
  void put_in(PuzzleState *elem);
  PuzzleState *take_out();
  bool is_empty();
  virtual ~LinkedListQueue();

 private:
  struct node{
    node* next;
    PuzzleState *data;
  };
    
  node* head;
  node* tail;
  int size;
};

#endif
