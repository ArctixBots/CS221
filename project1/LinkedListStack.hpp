//LinkedListStack.hpp
#ifndef _LINKEDLISTSTACK_HPP
#define _LINKEDLISTSTACK_HPP

#include "BagOfPuzzleStates.hpp"


class LinkedListStack: public BagOfPuzzleStates
{
 public:
  LinkedListStack();
  void put_in(PuzzleState *elem);
  PuzzleState *take_out();
  bool is_empty();
  virtual ~LinkedListStack();

 private:
  struct node{
    PuzzleState *data;
    node* next;
  };
    
  node* top;
};

#endif
