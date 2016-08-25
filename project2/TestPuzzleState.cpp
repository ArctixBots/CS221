#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

#include "PuzzleState.hpp"
#include "TestPuzzleState.hpp"

TestPuzzleState::TestPuzzleState(string id, int bad, bool sol) : uniqId(id), badness(bad), solution(sol) {}

TestPuzzleState::TestPuzzleState(const TestPuzzleState& other) : uniqId(other.uniqId), badness(other.badness), solution(other.solution) { }

TestPuzzleState::~TestPuzzleState() {  }

bool TestPuzzleState::isSolution() {
  return solution;
}


vector<PuzzleState*> TestPuzzleState::getSuccessors() {
  vector<PuzzleState*> result;
  return result;
}

int TestPuzzleState::getBadness() {
  return badness;
}

string TestPuzzleState::getUniqId() {
  return uniqId;
}

void TestPuzzleState::print (ostream& out) {
  out << "TestPuzzleState " << uniqId << " " << badness << " " << solution << endl;
}
