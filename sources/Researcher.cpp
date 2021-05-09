#include "Researcher.hpp"
using namespace std;
namespace pandemic {
Player &Researcher::discover_cure(Color color) {
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
string Researcher::role() { return "Researcher"; }
} // namespace pandemic