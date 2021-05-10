#include "Scientist.hpp"
using namespace std;
namespace pandemic {
Player &Scientist::discover_cure(Color color) {
  if (!board.labExists(currentLoc)) {
    throw invalid_argument{"There is no research station in " +
                           Board::toString(currentLoc) + "."};
  }
  int nOc = numOfCards(color);
  const int PAYMENT_FOR_FINDING_THE_TREAT = n;
  if (nOc < PAYMENT_FOR_FINDING_THE_TREAT) {
    throw invalid_argument{"You have only " + to_string(nOc) +
                           " cards remaining ."};
  }
  discard(color, PAYMENT_FOR_FINDING_THE_TREAT);
  board.addCure(color);
  return *this;
}
string Scientist::role() { return "Scientist"; }
} // namespace pandemic
