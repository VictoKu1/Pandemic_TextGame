#include "GeneSplicer.hpp"
using namespace std;
namespace pandemic {
Player &GeneSplicer::discover_cure(Color color) {
  if (!board.labExists(currentLoc)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(currentLoc) + "."};
  }
  int nOc = numOfCards();
  const int PAYMENT_FOR_FINDING_THE_TREAT = 5;
  if (nOc < PAYMENT_FOR_FINDING_THE_TREAT) {
    throw invalid_argument{"You have only " + to_string(nOc) +
                           " cards remaining ."};
  }
  discard(PAYMENT_FOR_FINDING_THE_TREAT);
  board.addCure(color);
  return *this;
}
string GeneSplicer::role() { return "GeneSplicer"; }
void GeneSplicer::discard(int amount) {
  set<City> clearList;
  for (const auto &city : cards) {
    clearList.insert(city);
  }
  for (const auto &city : clearList) {
    if (amount > 0) {
      cards.erase(city);
      amount-=1;
    } else {
      return;
    }
  }
}
int GeneSplicer::numOfCards() { return cards.size(); }
} // namespace pandemic