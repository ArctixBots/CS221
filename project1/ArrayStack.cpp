#ifndef _ARRAYSTACK_CPP
#define _ARRAYSTACK_CPP

//ArrayStack.cpp

#include "ArrayStack.hpp"
//#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
//using namespace std;

ArrayStack::ArrayStack() : top(0)
{
  array = new PuzzleState*[INIT_SIZE];
  capacity = INIT_SIZE;
}

void ArrayStack::put_in(PuzzleState *elem)
{
  ensure_capacity(top+1);
  array[top] = elem;
  top++;
}

PuzzleState *ArrayStack::take_out()
{
  assert(!is_empty());
  top--;
  return array[top];
}

bool ArrayStack::is_empty()
{
  return top == 0;
}

void ArrayStack::ensure_capacity(int n)
{
  if (capacity < n) {
    // Make plenty of room.
    int target_capacity = (n > 2*capacity+1) ? n : (2*capacity+1);

    // Set the current array aside and make room for the new one.
    PuzzleState **oldarray = array;
    array = new PuzzleState*[target_capacity];

    // Copy each element of the old array over.
    for (int i = 0; i < top; i++) {
      array[i] = oldarray[i];
    }

    capacity = target_capacity;

    delete [] oldarray;
  }
}


ArrayStack::~ArrayStack()
{
  delete [] array;
}

#endif
