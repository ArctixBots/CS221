//LinkedListDict.hpp
#ifndef _LINKEDLISTDICT_HPP
#define _LINKEDLISTDICT_HPP

#include "PredDict.hpp"

// An implementation of a dictionary ADT as an unsorted linked list.
// This will be very slow.
//
class LinkedListDict : public PredDict
  {
  public:
    LinkedListDict();
    ~LinkedListDict();
    bool find(PuzzleState *key, PuzzleState *&pred);
    void add(PuzzleState *key, PuzzleState *pred);

  private:
    struct node {
      PuzzleState *key;
      string keyID; // Saved copy of key's getUniqId()
      PuzzleState *data;
      node *next;
    };

    node *root;

    bool find_helper(node *r, string keyID, PuzzleState *&pred);
  };

#endif

