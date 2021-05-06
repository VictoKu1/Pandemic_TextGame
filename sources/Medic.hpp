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
class Medic : public Player {
public:
  Medic(Board &board, City city) : Player(board, city) {} 
  ~Medic() {}
  Player &treat(City city) override;
  string role() override;
};
} // namespace pandemic