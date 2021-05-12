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

void scatter(int numOfCubes, Player *player) {
  while (numOfCubes > 0) {
    City city = cityRandomizer();
    board[city] += 1;
    numOfCubes -= 1;
  }
}

void showOptions(Player *player) {
  system("clear");
  cout << "Cards left: " << to_string((*player).numOfCards()) << endl;
  cout << "Cubes left: " << to_string(board.numOfCubes()) << endl;
  cout << "Location: " << Board::toString((*player).getLocation()) << endl;
  cout << "\nOptions:" << endl;
  cout << "Press for each option its relevant number." << endl;
  cout << " 0 - Show board info.\n 1 - Drive.\n 2 - Direct-Flight.\n 3 - "
          "Charter-Flight.\n 4 - Charter-Flight.\n 5 - Build.\n 6 - "
          "Discover-Cure.\n 7 - Treat."
       << endl;
}

void drive(Player *player) {
  // cout << "Available roads :" << endl;
  // cout << board.connections((*player).getLocation()) << endl; //*TODO
  for (;;) {
    try {
      cout << "Enter the number of the relevant city you want to go to."
           << endl;
      int address = numInput(0, 48);
      (*player).drive(static_cast<City>(address));
      return;
    } catch (exception &ex) {
      cout << ex.what() << endl;
    }
  }
}

void flyDirect(Player *player) {
  // cout << "Available cards :" << endl;
  // cout << (*player).availableCardString() << endl; //*TODO
  for (;;) {
    try {
      cout << "Enter the number of the relevant city you want to go to."
           << endl;
      int address = numInput(0, 48);
      (*player).fly_direct(static_cast<City>(address));
      return;
    } catch (exception &ex) {
      cout << ex.what() << endl;
    }
  }
}

void flyCharter(Player *player) {
  // cout << "Cities relevant code list :" << endl;
  // cout << printCityString() << endl; //*TODO
  for (;;) {
    cerr.clear();
    try {
      cout << "Enter the number of the relevant city you want to go to."
           << endl;
      int address = numInput(0, 48);
      (*player).fly_charter(static_cast<City>(address));
      return;
    } catch (exception &ex) {
      cin.clear();
      std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
      cout << ex.what() << endl;
      cout << "Enter the number of the relevant city you want to treat."
           << endl;
      int address = numInput(0, 48);
      continue;
    }
  }
}

void flyShuttle(Player *player) {
  // cout << "Cities relevant code list :" << endl;
  // cout << printCityString() << endl; //*TODO
  for (;;) {
    try {
      cout << "Enter the number of the relevant city you want to go to."
           << endl;
      int address = numInput(0, 48);
      (*player).fly_shuttle(static_cast<City>(address));
      return;
    } catch (exception &ex) {
      cout << ex.what() << endl;
    }
  }
}

void build(Player *player) {
  try {
    (*player).build();
  } catch (exception &ex) {
    cout << ex.what() << endl;
    usleep(1000000);
  }
  return;
}

void discoverCure(Player *player) {
  // cout << "Available cards :" << endl;
  // cout << board.toColorString((*player).getCards()) << endl; //*TODO
  for (;;) {
    try {
      cout << "Enter the number of the relevant color you want to discover the "
              "cure for ."
           << endl;
      int color = numInput(0, 3);
      (*player).discover_cure(static_cast<Color>(color));
      return;
    } catch (exception &ex) {
      cout << ex.what() << endl;
      ;
    }
  }
}

void treat(Player *player) {
  for (;;) {
    try {
      cout << "Enter the number of the relevant city you want to treat."
           << endl;
      int address = numInput(0, 48);
      (*player).treat(static_cast<City>(address));
      return;
    } catch (exception &ex) {
      cout << ex.what() << endl;
    }
  }
}

void round(Player *player, int level) {
  system("clear");
  cout << "Level: " << level << endl;
  usleep(500000);
  int numOfCubes = rand() % 49;
  cout << numOfCubes << " cubes are being scattered randomly ." << endl;
  usleep(500000);
  scatter(numOfCubes, player);
  int i = 0;
  cout << "You've got the following cards :\n(you get them randomly so if "
          "you'll get some card twise it'll count as a losing the doubled "
          "card) ."
       << endl;
  int input = rand() % 49;
  while (i < input) {
    City city = cityRandomizer();
    (*player).take_card(city);
    cout << Board::toString(city) << endl;
    i += 1;
  }
  usleep(1000000);
  for (;;) {
    if (!(*player).hasCards()) {
      break;
    }
    showOptions(player);
    int choice = numInput(0, 7);
    switch (choice) {
    case 0:
      cout << board << "\n___________________________\n" << (*player) << endl;
      usleep(10000000);
      break;
    case 1:
      drive(player);
      break;
    case 2:
      flyDirect(player);
      break;
    case 3:
      flyCharter(player);
      break;
    case 4:
      flyShuttle(player);
      break;
    case 5:
      build(player);
      break;
    case 6:
      discoverCure(player);
      break;
    case 7:
      treat(player);
      break;
    }
  }
  cout << "You're out of cards ." << endl;
  system("clear");
  if (board.is_clean()) {
    cout << "You won !\nAfter " << level << " levels, good job !" << endl;
    return;
  }
  cout << "There are still some infected cities left." << endl;
  cout << "Next round then." << endl;
  level += 1;
  round(player, level);
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
  int level = 1;
  round(player, level);
  delete player;
  return 0;
}
