//* Just sketches nothing smart here.
#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include <map>
#include <set>
#include <string>
using namespace std;
namespace pandemic {
class GeneSplicer : public Player {
public:
  GeneSplicer(Board &board, City city) : Player(board, city) {}
  ~GeneSplicer(){}
  Player &discover_cure(Color color) override;
  string role() override;
};
} // namespace pandemic