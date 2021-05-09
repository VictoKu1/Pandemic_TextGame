#include "Dispatcher.hpp"
using namespace std;
namespace pandemic {
Player &Dispatcher::fly_direct(City city) {
  if (board.labExists(city)) {
    currentLoc = city;
  } else {
    if (!hasCard(city)) {
      throw invalid_argument{"You dont have the card of " + Board::toString(city) + "."};
    }
    cards.erase(city);
    currentLoc = city;
  }
  return *this;
}
string Dispatcher::role() { return "Dispatcher"; }
} // namespace pandemic