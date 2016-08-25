#ifndef _STDSTACK_CPP
#define _STDSTACK_CPP

//StdStack.cpp

#include "StdStack.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
using namespace std;

StdStack::StdStack()
{
}

void StdStack::put_in(PuzzleState *elem)
{
  bag.push(elem);
}

PuzzleState *StdStack::take_out()
{
  assert(!is_empty());
  PuzzleState *temp = bag.top();
  bag.pop();
  return temp;
}

bool StdStack::is_empty()
{
  return bag.empty();
}

StdStack::~StdStack()
{
}

#endif
