#include "FieldDoctor.hpp"
using namespace std;
namespace pandemic {
Player &FieldDoctor::treat(City city) {
  if (board[city] == 0) {
    throw invalid_argument{"No more cubes remain in " + Board::toString(city) +
                           " ."};
  }
  if (!board.isConnected(currentLoc, city) && currentLoc != city) {
    throw invalid_argument{"To treat you need to be located in " +
                           Board::toString(city) + ", or any connected city."};
  }
  if (cureExist(city)) {
    useCure(city);
  } else {
    board[city] -= 1;
  }
  return *this;
}
string FieldDoctor::role() { return "FieldDoctor"; }
} // namespace pandemic