const int INT_MAX = 2147483647;
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unistd.h>
using namespace std;
using namespace pandemic;
Board board;
void intro() {
  cout << "Pandemic" << endl;
  usleep(1000000);
  for (int i = 5; i >= 0; --i) {
    system("clear");
    cout << to_string(i) << "\n";
    usleep(500000);
  }
  system("clear");
  cout << "Lets Go !" << endl;
  usleep(500000);
  system("clear");
}
int numInput(int min, int max) {
  int input;
  for (;;) {
    if (cin >> input) {
      if (min <= input && input <= max) {
        system("clear");
        break;
      }
    }
    cout << "Wrong input ." << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }
  return input;
}
string stringInput() {
  string input;
  for (;;) {
    if (getline(cin, input)) {
      system("clear");
      break;
    }
    cout << "Wrong input ." << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
  }
  return input;
}
City cityRandomizer() { return static_cast<City>(rand() % 48); }
Player *playerDetermine(int identifier) {
  City city = cityRandomizer();
  switch (identifier) {
  case 0: {
    cout << "You've choosen to play as OperationsExpert ." << endl;
    return new OperationsExpert(board, city);
  }
  case 1: {
    cout << "You've choosen to play as Dispatcher ." << endl;
    return new Dispatcher(board, city);
  }
  case 2: {
    int n = ((rand() % 5) + 1);
    cout << "You've choosen to play as Scientist .\n" << endl;
    cout << "The scientist will be able to discover the cure in (randomly "
            "generated number) "
         << n << " steps." << endl;
    return new Scientist(board, city, n);
  }
  case 3: {
    cout << "You've choosen to play as Researcher .\n" << endl;
    return new Researcher(board, city);
  }
  case 4: {
    cout << "You've choosen to play as Virologist .\n" << endl;
    return new Virologist(board, city);
  }
  case 5: {
    cout << "You've choosen to play as GeneSplicer .\n" << endl;
    return new GeneSplicer(board, city);
  }
  default: {
    cout << "You've choosen to play as FieldDoctor .\n" << endl;
    return new FieldDoctor(board, city);
  }
  }
}
void round(Player *player) {
  
}
int main() {
  system("clear");
  intro();
  cout << "Choose your class by entering its relevant index :" << endl;
  cout << "0 - OperationsExpert\n1 - Dispatcher\n2 - Scientist\n3 - "
          "Researcher\n4 - Virologist\n5 - GeneSplicer\n6 - FieldDoctor\n"
       << endl;
  int input = numInput(0, 6);
  Player *player = playerDetermine(input);
  cout << "Randomly generated first city: "
       << Board::toString((*player).getLocation()) << endl;
  cout << "\nHow many cards you want to take (please enter a number)?" << endl;
  input = numInput(0, 47);
  int i = 0;
  cout << "You've got the following cards :\n(you get them randomly so if "
          "you'll get some card twise it'll count as a losing the doubled "
          "card) ."
       << endl;
  while (i < input) {
    City city = cityRandomizer();
    (*player).take_card(city);
    cout << Board ::toString(city) << endl;
    i += 1;
  }
  round(player);
  delete player;
  return 0;
}
