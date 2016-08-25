#ifndef _STDQUEUE_CPP
#define _STDQUEUE_CPP

//StdQueue.cpp

#include "StdQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
using namespace std;

StdQueue::StdQueue()
{
}

void StdQueue::put_in(PuzzleState *elem)
{
  bag.push(elem);
}

PuzzleState *StdQueue::take_out()
{
  assert(!is_empty());
  PuzzleState *temp = bag.front();
  bag.pop();
  return temp;
}

bool StdQueue::is_empty()
{
  return bag.empty();
}

StdQueue::~StdQueue()
{
}

#endif
