//ResizeChainHashDict.hpp
#ifndef _RESIZECHAINHASHDICT_HPP
#define _RESIZECHAINHASHDICT_HPP

#include "PredDict.hpp"

// An implementation of a dictionary as a *resizable* hash table with
// chaining.

class ResizeChainHashDict : public PredDict
  {
  public:
    ResizeChainHashDict();
    ~ResizeChainHashDict();
    bool find(PuzzleState *key, PuzzleState *&pred);
    void add(PuzzleState *key, PuzzleState *pred);

  private:
    // You are allowed to change this if you need to, but be sure to
    // keep the structure where you compute key->getUniqId() ONCE
    // when you add a PuzzleState to the hash table, and then
    // store the UniqId string in keyID.  Then, when you do a
    // find, have a helper function that calls getUniqId() once
    // for the PuzzleState being searched for, and does all the
    // comparisons on strings.  This is much more efficient than
    // calling getUniqId() repeatedly.
    struct ChainNode {
      PuzzleState *key; // NULL indicates empty bucket.
      string keyID; // Avoid recomputation of key's getUniqId()
      PuzzleState *data;
      ChainNode *next;
    };

    // A pointer to the underlying hash table array, with elements
    // of type (ChainNode *).  We use an explicit pointer, instead of
    // declaring "ChainNode * table[size]" so you can resize the table.
    // This is similar to ArrayStack and ArrayQueue in your first project.
    ChainNode **table;
    int size; // current size of the hash table array
    const static int primes[]; // table of good primes for table size
    int size_index; // index of the current table size in the primes[] array
                    // Invariant:  size == primes[size_index]
    int number; // how many items are currently in hash table

    // The next two variables are just to collect statistics on the
    // number of probes required for each call to find().
    int *probes_stats; // probe_stats[i] should be how often i probes needed
    const static int MAX_STATS = 20; // How big to make the array.

    int hash(string keyID); // The hash function
    void rehash(); // Resizes to next bigger table and rehashes everything
  };

#endif

