#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <string>
using namespace std;
namespace pandemic {
class Player {
protected:
  Board &board;
  set<City> cards;
  City currentLoc;

  bool hasCard(City city);
  int numOfCards(Color color);
  void discard(Color color, int amount);
  bool cureExist(City city);
  void useCure(City city);

public:
  Player(Board &board, City currentLoc)
      : board(board), currentLoc(currentLoc) {}
  virtual ~Player() {}
  Player &drive(City city);
  virtual Player &
  fly_direct(City city); //* For special dispatcher implementation .
  Player &fly_charter(City city);
  Player &fly_shuttle(City city);
  virtual Player &build(); //*For special OperationExpert implementation .
  virtual Player &
  discover_cure(Color color);       //*For special Scientist/Researcher and
                                    //GeneSplicer implementation .
  virtual Player &treat(City city); //*For special Medic/Virologist and
                                    //FieldDoctor implementation .
  Player &take_card(City city);
  virtual string role(); //*For everyone special implemetation .
  Player &remove_cards();
  virtual void move(City city);
  City getLocation() { return currentLoc; }
};
} // namespace pandemic