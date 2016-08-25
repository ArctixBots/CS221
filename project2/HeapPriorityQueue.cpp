//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
  // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
  // no clean-up to do, since the heap is not dynamically allocated
}

void HeapPriorityQueue::put_in(PuzzleState *elem) {
  heap.push_back(elem);
  int pos = heap.size()-1;
  while(pos != 0 && heap[pos]->getBadness() < heap[pos/2]->getBadness()) {
      PuzzleState * a = heap[pos];
      heap[pos] = heap[pos/2];
      heap[pos/2] = a;
      pos = pos/2;
  }
}

PuzzleState * HeapPriorityQueue::take_out() {
  assert(!is_empty());

  PuzzleState * min = heap.front();
  heap[0] = heap.back();
  heap.pop_back();

  int hole = 0;
  while (2*hole+1 < heap.size()) {
    int target;
    int left = 2*hole + 1;
    int right = left + 1;
    if (right < heap.size() && heap[right]->getBadness() < heap[left]->getBadness()) {
      target = right;
    } else {
      target = left;
    }
    if (heap[target]->getBadness() < heap[hole]->getBadness()) {
      PuzzleState * h = heap[hole];
      heap[hole] = heap[target];
      heap[target] = h;
      hole = target;
    } else {
      break;
    }
  }
  return min;
}


bool HeapPriorityQueue::is_empty() {
  return (heap.size() == 0);
}

int HeapPriorityQueue::parent(int index) {
  return (index - 1) / 2;
}

int HeapPriorityQueue::first_child(int index) {
  return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
  return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
  return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
  int fchild = first_child(index);
  return max(0, min(2, (int)heap.size() - fchild));
}

#endif
