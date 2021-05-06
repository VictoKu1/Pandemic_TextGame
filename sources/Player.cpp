//*Nothing here works.
#include "Player.hpp"
#include <stdexcept>
using namespace std;
namespace pandemic {
bool Player::hasCard(City city) { return (cards.count(city) != 0); }
Player &Player::drive(City city) {
  if (!hasCard(city)) {
    return *this;
  }
  if (Board::isConnected(currentLoc, city)) {
    cards.erase(city);
    currentLoc = city;
    return *this;
  }
  return *this;
}
Player &Player::fly_direct(City city) {
  if (!hasCard(city)) {
    return *this;
  }
  currentLoc = city;
  cards.erase(city);
  return *this;
}
Player &Player::fly_charter(City city) {
  if (!hasCard(city)) {
    return *this;
  }
  if (hasCard(currentLoc)) {
    currentLoc = city;
    cards.erase(currentLoc);
    return *this;
  }
  return *this;
}
Player &Player::fly_shuttle(City city) {
  if (Board::labExists(currentLoc)) {
    if (Board::labExists(city)) {
      cards.erase(currentLoc);
      return *this;
    }
    return *this;
  }
  return *this;
}
Player &Player::build() {
  if (Board::labExists(currentLoc)) {
    return *this;
  }
  Board::makeLab(currentLoc);
  return *this;
}
Player &Player::discover_cure(Color color) {
  //*TODO.
  return *this;
}
Player &Player::treat(City city) {
  //*TODO.
  return *this;
}
Player &Player::take_card(City city) {
  //*TODO.
  return *this;
}
} // namespace pandemic