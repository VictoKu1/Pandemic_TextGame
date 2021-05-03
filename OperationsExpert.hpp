//* Just sketches nothing smart here.
#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <string>
using namespace std;
namespace pandemic {
class OperationsExpert : public Player {
public:
  OperationsExpert(Board &board, City city) : Player(board, city) {}
  ~OperationsExpert(){}
  Player &build() override;
  string role() override;
};
} // namespace pandemic