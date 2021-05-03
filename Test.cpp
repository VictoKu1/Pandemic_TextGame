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
#include "doctest.h"
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace pandemic;
class Loc {
public:
  set<City> connections;
  Color color;
  Loc() {}
  Loc(Color color, set<City> connections)
      : color{color}, connections{connections} {}
};
const map<City, Loc> c{
    {Algiers, {Black, {Madrid, Paris, Istanbul, Cairo}}},
    {Atlanta, {Blue, {Chicago, Miami, Washington}}},
    {Baghdad, {Black, {Tehran, Istanbul, Cairo, Riyadh, Karachi}}},
    {Bangkok, {Red, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong}}},
    {Beijing, {Red, {Shanghai, Seoul}}},
    {Bogota, {Yellow, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires}}},
    {BuenosAires, {Yellow, {Bogota, SaoPaulo}}},
    {Cairo, {Black, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh}}},
    {Chennai, {Black, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta}}},
    {Chicago,
     {Blue, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal}}},
    {Delhi, {Black, {Tehran, Karachi, Mumbai, Chennai, Kolkata}}},
    {Essen, {Blue, {London, Paris, Milan, StPetersburg}}},
    {HoChiMinhCity, {Red, {Jakarta, Bangkok, HongKong, Manila}}},
    {HongKong,
     {Red, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei}}},
    {Istanbul, {Black, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow}}},
    {Jakarta, {Red, {Chennai, Bangkok, HoChiMinhCity, Sydney}}},
    {Johannesburg, {Yellow, {Kinshasa, Khartoum}}},
    {Karachi, {Black, {Tehran, Baghdad, Riyadh, Mumbai, Delhi}}},
    {Khartoum, {Yellow, {Cairo, Lagos, Kinshasa, Johannesburg}}},
    {Kinshasa, {Yellow, {Lagos, Khartoum, Johannesburg}}},
    {Kolkata, {Black, {Delhi, Chennai, Bangkok, HongKong}}},
    {Lagos, {Yellow, {SaoPaulo, Khartoum, Kinshasa}}},
    {Lima, {Yellow, {MexicoCity, Bogota, Santiago}}},
    {London, {Blue, {NewYork, Madrid, Essen, Paris}}},
    {LosAngeles, {Yellow, {SanFrancisco, Chicago, MexicoCity, Sydney}}},
    {Madrid, {Blue, {London, NewYork, Paris, SaoPaulo, Algiers}}},
    {Manila, {Red, {Taipei, SanFrancisco, HoChiMinhCity, Sydney}}},
    {MexicoCity, {Yellow, {LosAngeles, Chicago, Miami, Lima, Bogota}}},
    {Miami, {Yellow, {Atlanta, MexicoCity, Washington, Bogota}}},
    {Milan, {Blue, {Essen, Paris, Istanbul}}},
    {Montreal, {Blue, {Chicago, Washington, NewYork}}},
    {Moscow, {Black, {StPetersburg, Istanbul, Tehran}}},
    {Mumbai, {Black, {Karachi, Delhi, Chennai}}},
    {NewYork, {Blue, {Montreal, Washington, London, Madrid}}},
    {Osaka, {Red, {Taipei, Tokyo}}},
    {Paris, {Blue, {Algiers, Essen, Madrid, Milan, London}}},
    {Riyadh, {Black, {Baghdad, Cairo, Karachi}}},
    {SanFrancisco, {Blue, {LosAngeles, Chicago, Tokyo, Manila}}},
    {Santiago, {Yellow, {Lima}}},
    {SaoPaulo, {Yellow, {Bogota, BuenosAires, Lagos, Madrid}}},
    {Seoul, {Red, {Beijing, Shanghai, Tokyo}}},
    {Shanghai, {Red, {Beijing, HongKong, Taipei, Seoul, Tokyo}}},
    {StPetersburg, {Blue, {Essen, Istanbul, Moscow}}},
    {Sydney, {Red, {Jakarta, Manila, LosAngeles}}},
    {Taipei, {Red, {Shanghai, HongKong, Osaka, Manila}}},
    {Tehran, {Black, {Baghdad, Moscow, Karachi, Delhi}}},
    {Tokyo, {Red, {Seoul, Shanghai, Osaka, SanFrancisco}}},
    {Washington, {Blue, {Atlanta, NewYork, Montreal, Miami}}}};
TEST_CASE("Right connectivity test.") {
  for (auto &source : c) {
    for (auto &dest : source.second.connections) {
      Board board;
      OperationsExpert builder{board, dest};
      CHECK_NOTHROW(builder.drive(dest));
      CHECK_NOTHROW(builder.drive(source.first));
    }
  }
}
TEST_CASE("Right color classification.") {
  for (auto &place : c) {
    Board board;
    OperationsExpert builder{board, place.first};
    board[place.first] = 1;
    builder.take_card(place.first);
    CHECK_NOTHROW(builder.discover_cure(place.second.color));
  }
}
TEST_CASE("Demo1 as test.") {
  Board board;
  board[City::Kinshasa] = 3;
  board[City::Kinshasa] = 2;
  board[City::MexicoCity] = 3;
  board[City::HoChiMinhCity] = 1;
  board[City::Chicago] = 1;
  OperationsExpert player{board, City::Atlanta};
  player.take_card(City::Johannesburg)
      .take_card(City::Khartoum)
      .take_card(City::SaoPaulo)
      .take_card(City::BuenosAires)
      .take_card(City::HoChiMinhCity);
  CHECK_NOTHROW(player.build());
  CHECK_NOTHROW(player.drive(City::Washington));
  CHECK_THROWS(player.drive(City::Madrid));
  CHECK_NOTHROW(player.fly_direct(City::Johannesburg));
  CHECK_THROWS(player.fly_direct(City::Taipei));
  CHECK_NOTHROW(player.drive(City::Kinshasa));
  CHECK_NOTHROW(player.treat(City::Kinshasa));
  CHECK_NOTHROW(player.treat(City::Kinshasa));
  CHECK_THROWS(player.treat(City::Kinshasa));
}
TEST_CASE("Empty board test.") {
  Board board;
  CHECK_FALSE(board.is_clean());
}
TEST_CASE("Right role name.") {
  {
    Board board;
    Player *player;
    player = new OperationsExpert(board, Johannesburg);
    CHECK((*player).role() == "OperationsExpert");
    delete player;
  }
  {
    Board board;
    OperationsExpert builder{board, City::Atlanta};
    CHECK(builder.role() == "OperationsExpert");
  }
  {
    Board board;
    FieldDoctor fieldDoctor(board, City::Washington);
    CHECK(fieldDoctor.role() == "FieldDoctor");
  }
  {
    Board board;
    Virologist virologist(board, City::Washington);
    CHECK(virologist.role() == "Virologist");
  }
  {
    Board board;
    Medic medic(board, City::Washington);
    CHECK(medic.role() == "Medic");
  }
  {
    Board board;
    Dispatcher dispatcher(board, City::Washington);
    CHECK(dispatcher.role() == "Dispatcher");
  }
  {
    Board board;
    GeneSplicer geneSplicer(board, City::Washington);
    CHECK(geneSplicer.role() == "GeneSplicer");
  }
  {
    Board board;
    Researcher researcher(board, City::Washington);
    CHECK(researcher.role() == "Researcher");
  }
  {
    Board board;
    Scientist scientist(board, City::Washington, 4);
    CHECK(scientist.role() == "Scientist");
  }
}
