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
class Scientist : public Player {
private:
  int n;

public:
  Scientist(Board &board, City city, int n) : Player(board, city), n(n) {}
  ~Scientist() {}
  Player &discover_cure(Color color) override;
  string role() override;
};
} // namespace pandemic