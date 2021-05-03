#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
using namespace std;
namespace pandemic {
class Location {
public:
  set<City> connections;
  bool laboratoryEx;
  Color color;
  int numOfCubes;
  int originalCubeNum;
  Location() {
    connections = {};
    color = Blue;
    laboratoryEx = false;
    numOfCubes = 0;
    originalCubeNum = 0;
  }
  Location(Color color, set<City>connections)
      : color{color}, connections{move(connections)} {
    laboratoryEx = false;
    numOfCubes = 0;
  }
};

class Board {
  static map<City, Location> loc;

public:
  Board() {} //*TODO: Mannualy add all the connections .
  ~Board(){}
  int &operator[](City c);
  friend ostream &operator<<(ostream &os, const Board &board);
  static bool is_clean();
  static bool isConnected(City from, City to);
  static bool labExists(City city);
  static void makeLab(City city);
  static void remove_cures();
};
} // namespace pandemic