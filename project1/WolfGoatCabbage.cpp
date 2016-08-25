#include <iostream>
#include <sstream>
using namespace std;

#include "PuzzleState.hpp"
#include "WolfGoatCabbage.hpp"

WolfGoatCabbage::WolfGoatCabbage() : boat(0), wolf(0), goat(0), cabbage(0) { }

WolfGoatCabbage::WolfGoatCabbage(int b, int w, int g, int c)
  : PuzzleState(), boat(b), wolf(w), goat(g), cabbage(c) { }

WolfGoatCabbage::~WolfGoatCabbage() { }

bool WolfGoatCabbage::isSolution() {
  // We've solved it if we've gotten everything across the river.
  return boat && wolf && goat && cabbage;
}

vector<PuzzleState*> WolfGoatCabbage::getSuccessors() {
  vector<PuzzleState*> result;

  // Can human row across with empty boat?
  if (wolf==goat) {
    // Wolf eats the goat when boat leaves.  Not OK
  } else if (goat==cabbage) {
    // Goat eats the cabbage when boat leaves.  Not OK
  } else {
    result.push_back(new WolfGoatCabbage(!boat,wolf,goat,cabbage));
  }

  // Can human row across with wolf?
  if (boat==wolf) {
    if (goat==cabbage) {
      // Goat eats the cabbage when boat leaves.  Not OK
    } else {
      result.push_back(new WolfGoatCabbage(!boat,!wolf,goat,cabbage));
    }
  }

  // Can human row across with goat?
  if (boat==goat) {
    result.push_back(new WolfGoatCabbage(!boat,wolf,!goat,cabbage));
  }

  // Can human row across with cabbage?
  if (boat==cabbage) {
    if (wolf==goat) {
      // Wolf eats the goat when boat leaves.  Not OK
    } else {
      result.push_back(new WolfGoatCabbage(!boat,wolf,goat,!cabbage));
    }
  }

  return result;
}

int WolfGoatCabbage::getBadness() {
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.

  // The more stuff across the river, the better?
  return -(boat+wolf+goat+cabbage);
}

string WolfGoatCabbage::getUniqId(void) {
  // This is a bit of a kludge, but it's easy.
  // We'll just use the print method to convert the PuzzleState
  // into a string representation.
  ostringstream temp;
  print(temp);
  return temp.str();
}

void WolfGoatCabbage::print (ostream& out) {
  if (!boat) out << "boat "; else out << "     ";
  if (!wolf) out << "wolf "; else out << "     ";
  if (!goat) out << "goat "; else out << "     ";
  if (!cabbage) out << "cabbage "; else out << "        ";

  out << "\\___river___/ ";

  if (boat) out << "boat "; else out << "     ";
  if (wolf) out << "wolf "; else out << "     ";
  if (goat) out << "goat "; else out << "     ";
  if (cabbage) out << "cabbage "; else out << "        ";

  out << endl;
}
