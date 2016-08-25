#ifndef _FIXEDCHAINHASHDICT_CPP
#define _FIXEDCHAINHASHDICT_CPP

//FixedChainHashDict.cpp
#include "FixedChainHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of the dictionary ADT as a fixed-size hash table with
// chaining

FixedChainHashDict::FixedChainHashDict(int table_size) {
  size = table_size;
  table = new ChainNode*[size](); // Parentheses initialize to all NULL
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
}

FixedChainHashDict::~FixedChainHashDict() {
  for (int i=0; i<size; i++) {
    // Delete the chains from each table entry...
    ChainNode *head = table[i];
    while (head!=NULL) {
      ChainNode *temp = head;
      head = head->next;
      delete temp->key;  // Each PuzzleState is a key exactly once.
      // Don't delete temp->data here, to avoid double deletions.
      delete temp;
    }
  }
  // Delete the table itself
  delete [] table;

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Probe Statistics for find():\n";
  for (int i=0; i<MAX_STATS; i++)
    cout << i << ": " << probes_stats[i] << endl;
  delete [] probes_stats;
}

int FixedChainHashDict::hash(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 31*h) % size;
  }
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Hashing " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
  return h;
}

bool FixedChainHashDict::find(PuzzleState *key, PuzzleState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred

  // Be sure not to keep calling getUniqId() over and over again!
  string uniqId = key->getUniqId();
  int h = hash(uniqId);
  int probes = 0;
  ChainNode * n = table[h];
  while (n != NULL && n->keyID != uniqId) {
    n = n->next;
    probes++;
  }
  if (probes < MAX_STATS) {
    probes_stats[probes]++;
  }
  if (n == NULL) {
    return false;
  }
  pred = n->data;
  return true;
}

// You may assume that no duplicate PuzzleState is ever added.
void FixedChainHashDict::add(PuzzleState *key, PuzzleState *pred) {
  ChainNode * n = new ChainNode;
  n->key = key;
  n->keyID = key->getUniqId();
  n->data = pred;
  int h = hash(n->keyID);
  n->next = table[h];
  table[h] = n;
}

#endif
