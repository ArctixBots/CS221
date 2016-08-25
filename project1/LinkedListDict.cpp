#ifndef _LINKEDLISTDICT_CPP
#define _LINKEDLISTDICT_CPP

//LinkedListDict.cpp
#include "LinkedListDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as an unsorted linked list.
//
LinkedListDict::LinkedListDict() {
  root = NULL;
}

LinkedListDict::~LinkedListDict() {
  // Ideally, we would recursively traverse the list to
  // delete all the nodes.  We'd also need to keep track of
  // whether or not to delete the data and key fields, which
  // can be very tricky (are there any other pointers to these
  // fields?)  The newest C++ has so-called smart pointers that
  // will do this for you, but fortunately for us, in our program
  // we never need to delete a dictionary.

  // So, we'll just do nothing in the destructor.
}

bool LinkedListDict::find_helper(node *r, PuzzleState *key, PuzzleState *&pred) {
  if (r==NULL) return false; // Never found it.
  if (key->getUniqId() == r->key->getUniqId()) {
    pred = r->data; // Got it!  Get the result.
    return true;
  }
  return find_helper(r->next, key, pred);
}

bool LinkedListDict::find(PuzzleState *key, PuzzleState *&pred) {
  return find_helper(root, key, pred);
}

void LinkedListDict::add(PuzzleState *key, PuzzleState *pred) {
  node * temp = new node();
  temp->key = key;
  temp->data = pred;
  temp->next = root;
  root = temp;
  return;
}

#endif 
