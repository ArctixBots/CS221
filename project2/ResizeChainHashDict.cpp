#ifndef _RESIZECHAINHASHDICT_CPP
#define _RESIZECHAINHASHDICT_CPP

//ResizeChainHashDict.cpp
#include "ResizeChainHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of the dictionary ADT as a resizable hash table with
// chaining

const int ResizeChainHashDict::primes[] = {53, 97, 193, 389, 769, 1543, 3079,
      6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869,
      3145739, 6291469, 12582917, 25165843, 50331653, 100663319,
      201326611, 402653189, 805306457, 1610612741, -1};
// List of good primes for hash table sizes from
// http://planetmath.org/goodhashtableprimes
// The -1 at the end is to guarantee an immediate crash if we run off
// the end of the array.

ResizeChainHashDict::ResizeChainHashDict() {
  size_index = 0;
  size = primes[size_index];
  table = new ChainNode*[size](); // Parentheses initialize to all NULL
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
}

ResizeChainHashDict::~ResizeChainHashDict() {
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

int ResizeChainHashDict::hash(string keyID) {
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

void ResizeChainHashDict::rehash() {
  // 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
  // And leave this at the beginning of the rehash() function.
  // We will use this code when marking to be able to watch what
  // your program is doing, so if you change things, we'll mark it wrong.
  std::cout << "*** REHASHING number=" << number << ", size changes from " << size;
  // End of "DO NOT CHANGE" Block

  // TODO:  Your code goes here...
  // Be very careful with memory leakage here.
  // When you rehash, you'll either want to unlink each ChainNode
  // from the old table and re-link it into the new one, or
  // you'll want to create a new ChainNode in the new table, and make
  // sure you delete the old ChainNode.  But don't delete the PuzzleStates.

  size_index++;
  int old_size = size;
  ChainNode** old_table = table;
  size = primes[size_index];
  table = new ChainNode*[size](); // Parentheses initialize to all NULL

  for (int i=0; i < old_size; i++) {
    ChainNode * node = old_table[i];
    while (node != NULL) {
      add(node->key, node->data);
      ChainNode * old = node;
      node = node->next;
      delete old;
    }
  }

  delete[] old_table;

  // 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
  // And leave this at the end of the rehash() function.
  // We will use this code when marking to be able to watch what
  // your program is doing, so if you change things, we'll mark it wrong.
  std::cout << " to " << size << " ***\n";
  // End of "DO NOT CHANGE" Block
}

bool ResizeChainHashDict::find(PuzzleState *key, PuzzleState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred

  // Be sure not to keep calling getUniqId() over and over again!

  // TODO:  Your code goes here...
  // Don't forget to update the probes_stats!

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
void ResizeChainHashDict::add(PuzzleState *key, PuzzleState *pred) {

  // Rehash if adding one more element pushes load factor over 1/2
  if (2*(number+1) > size) rehash();  // DO NOT CHANGE THIS LINE

  ChainNode * n = new ChainNode;
  n->key = key;
  n->keyID = key->getUniqId();
  n->data = pred;
  int h = hash(n->keyID);
  n->next = table[h];
  table[h] = n;

  number++;
}

#endif
