//*Nothing here works.
#include "Player.hpp"
#include "Board.hpp"
#include <stdexcept>
using namespace std;
namespace pandemic {
bool Player::hasCard(City city) { return (cards.count(city) != 0); }
Player &Player::drive(City city) {
  if(currentLoc == city){
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (board.isConnected(currentLoc, city)) {
    move(city);
    return *this;
  }
  return *this;
}
Player &Player::fly_direct(City city) {
  if(currentLoc == city){
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (!hasCard(city)) {
    throw invalid_argument{"You dont have the card of " +
                           Board::toString(city) + "."};
  }
  cards.erase(city);
  move(city);
  return *this;
}
Player &Player::fly_charter(City city) {
  if(currentLoc == city){
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (!hasCard(currentLoc)) {
    throw invalid_argument{"You dont have the " + Board::toString(currentLoc) +
                           " card (the card of the city you are in) ."};
  }
  cards.erase(currentLoc);
  move(city);
  return *this;
}
Player &Player::fly_shuttle(City city) {
  if(currentLoc == city){
    throw invalid_argument{"You cant move from the city to itself ."};
  }
  if (!board.labExists(currentLoc)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(currentLoc) + "."};
  }
  if (!board.labExists(city)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(city) + "."};
  }
  move(city);
  return *this;
}
Player &Player::build() {
  if (!hasCard(currentLoc)) {
    throw invalid_argument{"You dont have a card for " +
                           Board::toString(currentLoc) + "."};
  }
  board.makeLab(currentLoc);
  return *this;
}
Player &Player::discover_cure(Color color) {
  if (!board.labExists(currentLoc)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(currentLoc) + "."};
  }
  int nOc = numOfCards(color);
  const int PAYMENT_FOR_FINDING_THE_TREAT = 5;
  if (nOc < PAYMENT_FOR_FINDING_THE_TREAT) {
    throw invalid_argument{"You have only " + to_string(nOc) +
                           " cards remaining ."};
  }
  discard(color, PAYMENT_FOR_FINDING_THE_TREAT);
  board.addCure(color);
  return *this;
}
Player &Player::treat(City city) {
  if (board[city] == 0) {
    throw invalid_argument{"No more cubes remain in " + Board::toString(city) +
                           " ."};
  }
  if (currentLoc != city) {
    throw invalid_argument{"To treat you need to be located at " +
                           Board::toString(city) + "."};
  }
  if (cureExist(city)) {
    useCure(city);
  } else {
    board[city]--;
  }
  return *this;
}
Player &Player::take_card(City city) {
  cards.insert(city);
  return *this;
}
string Player::role() { return "Player."; }
Player &Player::remove_cards() {
  cards.clear();
  return *this;
}
int Player::numOfCards(Color color) {
  int counter = 0;
  for (const auto &city : cards) {
    if (board.colorOf(city) == color) {
      counter++;
    }
  }
  return counter;
}
void Player::discard(Color color, int amount) {
  set<City> clearList;
  for (const auto &city : cards) {
    if (board.colorOf(city) == color) {
      clearList.insert(city);
    }
  }
  for (const auto &city : clearList) {
    if (amount > 0) {
      cards.erase(city);
      amount--;
    } else {
      return;
    }
  }
}
bool Player::cureExist(City city) {
  return (board.getCureArray().at(board.colorOf(city)) > 0);
}

void Player::useCure(City city) {
  board[city] = 0;
}

void Player::move(City city) { 
  
  currentLoc = city; }
} // namespace pandemic
