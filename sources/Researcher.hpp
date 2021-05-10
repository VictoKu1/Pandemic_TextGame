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
class Researcher : public Player {
public:
  Researcher(Board &board, City city) : Player(board, city) {}
  ~Researcher() {}
  Player &discover_cure(Color color) override;
  string role() override;
};
} // namespace pandemic
