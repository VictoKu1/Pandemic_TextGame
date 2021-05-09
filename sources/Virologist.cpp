#include "Virologist.hpp"
using namespace std;
namespace pandemic {
Player &Virologist::treat(City city) {
  if (board[city] == 0) {
    throw invalid_argument{"No more cubes remain in " + Board::toString(city) +
                           " ."};
  }
  if (currentLoc != city) {
    if (!hasCard(city)) {
      throw invalid_argument{"To treat you need to have the card of " +
                             Board::toString(city) + "."};
    }
  }
  cards.erase(city);
  if (cureExist(city)) {
    useCure(city);
  } else {
    board[city]--;
  }
  return *this;
}
string Virologist::role() { return "Virologist"; }
} // namespace pandemic