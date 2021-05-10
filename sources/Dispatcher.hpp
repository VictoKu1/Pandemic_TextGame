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
class Dispatcher : public Player {
public:
  Dispatcher(Board &board, City city) : Player(board, city) {}
  ~Dispatcher(){}
  Player &fly_direct(City city) override;
  string role() override;
};
} // namespace pandemic


