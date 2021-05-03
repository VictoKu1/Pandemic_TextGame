/**
 * Demo program for Pandemic exercise - compares the different roles.
 *
 * Author: Erel Segal-Halevi
 * Since : 2021-04
 */

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"

using namespace pandemic;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

// Give some four red cards to the given player, to initialize an example.
void take_four_red_cards(Player &player) {
  player.take_card(City::Sydney)
      .take_card(City::HoChiMinhCity)
      .take_card(City::HongKong)
      .take_card(City::Bangkok);
}

// Checks if the given player can discover a cure.
bool can_discover_cure(Board &board, Player &player, Color color) {
  board.remove_cures();
  try {
    player.discover_cure(color);
    return true;
  } catch (const exception &ex) {
    return false;
  }
}

// Check the conditions in which the given player can discover a cure.
void check_cure_discovery(Board &board, Player &player) {
  cout << "Checking a " << player.role() << ": " << endl;

  take_four_red_cards(player);
  cout << "  Four red cards, no research station: "
       << can_discover_cure(board, player, Color::Red) << endl;

  take_four_red_cards(player);
  player.drive(City::Atlanta);
  cout << "  Four red cards, in a research station: "
       << can_discover_cure(board, player, Color::Red) << endl;

  take_four_red_cards(player);
  player.take_card(City::Cairo);
  cout << "  Four red cards and one black card, in a research station: "
       << can_discover_cure(board, player, Color::Red) << endl;

  take_four_red_cards(player);
  player.take_card(City::Beijing);
  player.drive(City::Washington);
  cout << "  Five red cards, no research station: "
       << can_discover_cure(board, player, Color::Red) << endl;

  take_four_red_cards(player);
  player.take_card(City::Beijing);
  player.drive(City::Atlanta);
  cout << "  Five red cards, in a research station: "
       << can_discover_cure(board, player, Color::Red) << endl;
}

int main() {
  cout << boolalpha;
  Board board;

  OperationsExpert builder{board, City::Atlanta};
  builder.build(); // Build a research station in Atlanta, to prepare the board
                   // for the tests.

  {
    FieldDoctor player(board, City::Washington);
    check_cure_discovery(board,
                         player); // should print: false false false false true
  }
  {
    Virologist player(board, City::Washington);
    check_cure_discovery(board,
                         player); // should print: false false false false true
  }
  {
    OperationsExpert player(board, City::Washington);
    check_cure_discovery(board,
                         player); // should print: false false false false true
  }
  {
    Medic player(board, City::Washington);
    check_cure_discovery(board,
                         player); // should print: false false false false true
  }
  {
    Dispatcher player(board, City::Washington);
    check_cure_discovery(board,
                         player); // should print: false false false false true
  }
  {
    GeneSplicer player(board, City::Washington);
    check_cure_discovery(
        board, player); // should print: false false ***true*** false true [can
                        // find a cure with 4 red and 1 black card]
  }
  {
    Researcher player(board, City::Washington);
    check_cure_discovery(
        board, player); // should print: false false false ***true*** true [can
                        // find a cure without a research station]
  }
  {
    Scientist player(board, City::Washington, 4);
    check_cure_discovery(
        board, player); // should print: false ***true*** ***true*** false true
                        // [can find a cure with only 4 red cards]
  }
}
