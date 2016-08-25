#ifndef _ARRAYQUEUE_CPP
#define _ARRAYQUEUE_CPP

// ArrayQueue.cpp

#include "ArrayQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
#include <cstring>
using namespace std;

// 221 STUDENTS:
//
// This skeleton file (along with the .hpp file) is here to help get you
// started, but you are free to change function signatures, etc. as
// long as ArrayQueue is derived from BagOfPuzzleStates.
ArrayQueue::ArrayQueue() {
  size = 0;
  capacity = 0;
  front = 0;
  back = 0;
  array = new PuzzleState *[0];
}

void ArrayQueue::put_in(PuzzleState *elem) {
  ensure_capacity(size + 1);
  back = (back + 1) % capacity;
  array[back] = elem;
  size++;
}

PuzzleState *ArrayQueue::take_out() {
  if (size == 0) {
    return NULL;
  }
  size--;
  PuzzleState *elem = array[front];
  front = (front + 1) % capacity;
  return elem;
}

bool ArrayQueue::is_empty() { return size == 0; }

void ArrayQueue::ensure_capacity(int n) {
  if (n > capacity) {
    // Make plenty of room.
    int target_capacity = capacity * 2;
    if (n > target_capacity) {
      target_capacity = n;
    }

    PuzzleState **n_array = new PuzzleState *[target_capacity];

    int s = sizeof(PuzzleState *);

    if (back >= front) {
      memmove(n_array, array + front * s, (back + 1 - front) * s);
    } else {
      memmove(n_array, array + front * s, (capacity - front) * s);
      memmove(n_array, array + (capacity - front) * s, (back + 1) * s);
    }
    front = 0;
    back = (size - 1) % target_capacity;

    delete[] array;

    array = n_array;
    capacity = target_capacity;
  }
}

ArrayQueue::~ArrayQueue() { delete[] array; }

#endif
