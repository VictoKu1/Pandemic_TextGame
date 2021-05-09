#include "OperationsExpert.hpp"
using namespace std;
namespace pandemic {
Player &OperationsExpert::build() {
  board.makeLab(currentLoc);
  return *this;
}
string OperationsExpert::role() { return "OperationsExpert"; }
} // namespace pandemic