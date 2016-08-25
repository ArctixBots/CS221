#include <iostream>
#include <fstream>
#include <iomanip>	// provides std::setw()
#include <cstdlib>	// provides atoi()
#include <cassert>      // provides assert
#include <functional>   // provides std::function

#include "Timer.h"

#define REPS 1

typedef std::string KType;
typedef int VType;

struct Node {
  KType key;
  VType value;
  int height;
  Node * left;
  Node * right;
};

Node* createNode( KType key, VType value, Node* l = NULL, Node* r = NULL ) {
  //
  // Creates a new Node containing key and value, with 'l' as its left
  // child and 'r' as its right child, with height=0
  //
  // PRE:  key is valid, l points to a Node or is NULL and r
  //       points to a Node or is NULL
  // POST: If there is enough free memory space, a new Node is created
  //	   and its address is returned; otherwise, NULL is returned.

  Node* result = new Node;
  result->key = key;
  result->value = value;
  result->height = 0;
  result->left = l;
  result->right = r;
  return result;
}

void deleteTree( Node*& root ) {
  //
  // Deletes a tree rooted at root
  //
  // PRE:  root is a valid Node address or NULL
  // POST: All the nodes in the tree rooted at root are deleted and
  //       root is set to NULL.

  if ( root != NULL ) {
    deleteTree( root->left );
    deleteTree( root->right );
    delete root;
    root = NULL;
  }
}

int height( Node * x ) {
  //
  // Returns the height of node x or -1 if x is NULL.
  //
  if( x == NULL ) return -1;
  return x->height;
}

bool updateHeight( Node * x ) {
  //
  // Recalculates the height of x from the height of its children.
  // Returns true iff the height of x changes.
  //
  if( x == NULL ) return false;
  int m = std::max(height(x->left), height(x->right)) + 1;
  if( x->height != m ) {
    x->height = m;
    return true;
  }
  return false;
}

void rotateLeft( Node *& b ) {
  Node * a = b->left;
  b->left = a->right;
  a->right = b;
  updateHeight(b);
  updateHeight(a);
  b = a;
}

void rotateRight( Node *& a ) {
  Node * b = a->right;
  a->right = b->left;
  b->left = a;
  updateHeight(a);
  updateHeight(b);
  a = b;
}

void doubleRotateLeft( Node *& c ) {
  rotateRight(c->left);
  rotateLeft(c);
}

void doubleRotateRight( Node *& a ) {
  rotateLeft(a->right);
  rotateRight(a);
}

void balance( Node *& x ) {
  //
  // Check if node x is unbalanced (i.e., the heights of its
  // two children differ by more than one).  If it is, rebalance
  // at x using one of rotateLeft, rotateRight, doubleRotateLeft,
  // or doubleRotateRight, whichever is appropriate.
  //
  if( x == NULL ) return;
  int b = height(x->left) - height(x->right);
  if( b >= -1 && b <= 1 ) return;
  if( b == 2 ) {
    if( height(x->left->left) > height(x->left->right) ) {
      rotateLeft(x);
    } else {
      doubleRotateLeft(x);
    }
  } else {
    if( height(x->right->right) > height(x->right->left) ) {
      rotateRight(x);
    } else {
      doubleRotateRight(x);
    }
  }
}

void insert( KType key, VType value, Node *& root ) {
  //
  // Insert key into the AVL tree rooted at root.
  // Restore balance if required.
  //
  if( root == NULL ) {
    root = createNode(key, value);
    return;
  }
  if( key < root->key ) {
    insert( key, value, root->left );
  } else {
    insert( key, value, root->right );
  }
  if( updateHeight(root) ) balance(root);
}

bool contains( KType key, Node * root ) {
  //
  // Return true iff the tree contains the given key.
  //
  if ( root == NULL ) {
    return false;
  }

  if ( key < root->key ) {
    return contains( key, root->left );
  }
  else if ( key > root->key ) {
    return contains( key, root->right );
  }
  else
    return true;
}

// Precondition: contains( key, root )
VType & lookup( KType key, Node * root ) {
  //
  // Return the value associated with key in the tree
  //
  assert ( root != NULL );

  if ( key < root->key ) {
    return lookup( key, root->left );
  }
  else if ( key > root->key ) {
    return lookup( key, root->right );
  }
  else
    return root->value;
}

void printTreeHelper( Node * r, int d ) {
//
// Prints out the tree sideways
//
// PRE:  root is a valid Node address
// POST: The tree rooted at r is printed in reverse inorder with nodes
//       indented 3 * d spaces; this produces a tree that has its root near
//       the left side of the screen and the leaves near the right side
  if( r == NULL ) return;
  printTreeHelper( r->right, d+1 );
  std::cout << std::setw( 3 * d ) << "";		// output 3 * d spaces
  std::cout << r->key << std::endl;
  printTreeHelper( r->left, d+1 );
}
void printTree( Node * r ) {
  printTreeHelper( r, 0 );
}

// keys to insert by default
int defaultKeys[] = {70, 10, 60, 20, 50, 30, 40, 25, 27, 5};

// Precondition: word and count are appropriate default values;
//               in particular, count is the minimum VType value
// Postcondition: count is the maximum value in the tree and word
//                is the key associated with that value
void findMaxSequential(Node * root, KType & word, VType & count) {
  if (root == NULL) {
    return;
  }

  // Find the max in the left subtree.
  KType lword;
  VType lmax = count;
  findMaxSequential(root->left, lword, lmax);

  // Find the max in the right subtree.
  KType rword;
  VType rmax = count;
  findMaxSequential(root->right, rword, rmax);

  // Record for return the largest of the left-max, right-max, and
  // current node's key/value.
  if (rmax > lmax && rmax > root->value) {
    word = rword;
    count = rmax;
  }
  else if (lmax > root->value) {
    word = lword;
    count = lmax;
  }
  else {
    word = root->key;
    count = root->value;
  }
}

// Precondition: word and count are appropriate default values;
//               in particular, count is the minimum VType value
// Postcondition: count is the maximum value in the tree and word
//                is the key associated with that value
void findMaxHelper(Node * root, KType & word, VType & count) {
  //
  // Uses divide-and-conquer, fork/join-style parallelism.  Your
  // solution should fork off tasks to handle subtrees until you can
  // guarantee by looking at the root node of a subtree that it has at
  // most 1100 nodes, at which point it should switch to the provided
  // sequential version instead.
  //

  // NOTE: be sure to look at findMax.  It's nothing much.. but it's
  // easy to forget when using OpenMP!

  if (root == NULL) {
    return;
  }
  if (root->height <= 9) {
    return findMaxSequential(root, word, count);
  }

  KType lword, rword;
  VType lmax = count;
  VType rmax = count;

  #pragma omp task untied shared(lword, lmax)
  { findMaxHelper(root->left, lword, lmax); }
  findMaxHelper(root->right, rword, rmax);
  #pragma omp taskwait
  if (rmax > lmax && rmax > root->value) {
    word = rword;
    count = rmax;
  }
  else if (lmax > root->value) {
    word = lword;
    count = lmax;
  }
  else {
    word = root->key;
    count = root->value;
  }
}


// Precondition: word and count are appropriate default values;
//               in particular, count is the minimum VType value
// Postcondition: count is the maximum value in the tree and word
//                is the key associated with that value
void findMax(Node * root, KType & word, VType & count) {
  // "Spin up" parallelism for OpenMP.
#pragma omp parallel
#pragma omp single
  findMaxHelper(root, word, count);
}

void usage(const char* program) {
  std::cout << "Usage: " << program << " <filename>" << std::endl;
  std::cout << "\tPrints the most common word (with its count) in the named file."
       << std::endl;
}

void findMostCommonAndReport(std::function<void(Node*, KType&, VType&)> f,
			     Node * tree, KType & k, VType & v,
			     const char * type) {
  KType kdefault = k;
  VType vdefault = v;

  Timer timer;
  for (int i = 0; i < REPS; i++) {
    KType knew = kdefault;
    VType vnew = vdefault;
    f(tree, knew, vnew);
    assert(i == 0 || (knew == k && vnew == v));
    k = knew;
    v = vnew;
  }
  auto time = timer.timeSoFar();
  std::chrono::duration<double> timeS = time;
  std::cout << type << "\t" << k << "\t" << v << "\t"
	    << timeS.count() << std::endl;
  std::cout.flush();
}

int main( int argc, char *argv[] ) {
  if (argc != 2) {
    usage(argv[0]);
    return -1;
  }

  std::ifstream in(argv[1]);

  // Tally all the words.
  Node *T = NULL;
  std::string word;
  while (in >> word) {
    if (!contains(word, T)) {
      insert(word, 1, T);
    }
    else {
      lookup(word, T)++;
    }
  }

  // Find the most common word.
  int count;
  word = "";
  count = 0;
  findMostCommonAndReport(&findMax, T, word, count, "para");

  word = "";
  count = 0;
  findMostCommonAndReport(&findMaxSequential, T, word, count, "seql");

  // Free up allocated memory
  deleteTree(T);

  return 0;
}

/*
rice@nicki [05:33:23] [~/Developer/cpsc221/lab9]
4)
-> % make && ./avl parallel-lab-resources/king_james_bible.txt
para    the     62257   0.00257228
seql    the     62257   0.00169611
rice@nicki [05:33:32] [~/Developer/cpsc221/lab9]
-> % make && ./avl parallel-lab-resources/a-few-google-5-grams.txt
para    the     2193538 0.00375234
seql    the     2193538 0.00137296
5) Sequential seems to be faster than the parallel version. Probably because this machine only has one core.

*/
