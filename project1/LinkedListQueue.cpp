// LinkedListQueue.cpp
#ifndef _LINKEDLISTQUEUE_CPP
#define _LINKEDLISTQUEUE_CPP

#include "LinkedListQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
LinkedListQueue::LinkedListQueue() {
  head = NULL;
  tail = NULL;
  size = 0;
}

void LinkedListQueue::put_in(PuzzleState *elem) {
  // TODO
  node *n = new node();
  n->data = elem;
  if (size == 0) {
    head = n;
    tail = n;
  } else {
    head->next = n;
    head = n;
  }
  size++;
}

PuzzleState *LinkedListQueue::take_out() {
  if (size == 0) {
    return NULL;
  }
  size--;
  node *n = tail;
  PuzzleState *data = tail->data;
  tail = tail->next;
  delete n;
  return data;
}

bool LinkedListQueue::is_empty() { return size == 0; }

LinkedListQueue::~LinkedListQueue() {
  node *n = tail;
  while (n != NULL) {
    delete n;
    n = n->next;
  }
}

#endif
