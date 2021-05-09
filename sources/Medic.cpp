#include "Medic.hpp"
using namespace std;
namespace pandemic {
Player &Medic::treat(City city) {
  if (board[city] == 0) {
    throw invalid_argument{"No more cubes remain in " + Board::toString(city) +
                           " ."};
  }
  if (currentLoc != city) {
    throw invalid_argument{"To treat you need to be located at " +
                           Board::toString(city) + "."};
  }
  useCure(city);
  return *this;
}
string Medic::role() { return "Medic"; }
void Medic::move(City city) {
  if (cureExist(city)) {
    board[city] = 0;
  }
  currentLoc = city;
}
} // namespace pandemic

