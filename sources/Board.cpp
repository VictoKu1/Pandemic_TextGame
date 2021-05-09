#include "Board.hpp"
#include <stdexcept>
using namespace std;
namespace pandemic {
int &Board::operator[](City city) { return loc[city].numOfCubes; }
ostream &operator<<(ostream &os, const Board &board) {
  return (os << "TODO." << endl);
}
bool Board::is_clean() {
  for (auto &place : (*this).loc) {
    if (place.second.numOfCubes > 0) {
      return false;
    }
  }
  return true;
}
bool Board::isConnected(City from, City to) {
  return (loc[from].connections.count(to) != 0);
}
bool Board::labExists(City city) { return (*this).loc[city].laboratoryEx; }
void Board::makeLab(City city) { (*this).loc[city].laboratoryEx = true; }
void Board::remove_cures() {
  for (auto &place : (*this).loc) {
    place.second.numOfCubes = place.second.originalCubeNum + 0;
  }
}
void Board::remove_stations() {
  for (auto &place : (*this).loc) {
    place.second.laboratoryEx = false;
  }
}
string Board::toString(City city) {
  switch (city) {
  case Algiers:
    return "Algiers";
    break;
  case Atlanta:
    return "Atlanta";
    break;
  case Baghdad:
    return "Baghdad";
    break;
  case Bangkok:
    return "Bangkok";
    break;
  case Beijing:
    return "Beijing";
    break;
  case Bogota:
    return "Bogota";
    break;
  case BuenosAires:
    return "BuenosAires";
    break;
  case Cairo:
    return "Cairo";
    break;
  case Chennai:
    return "Chennai";
    break;
  case Chicago:
    return "Chicago";
    break;
  case Delhi:
    return "Delhi";
    break;
  case Essen:
    return "Essen";
    break;
  case HoChiMinhCity:
    return "HoChiMinhCity";
    break;
  case HongKong:
    return "HongKong";
    break;
  case Istanbul:
    return "Istanbul";
    break;
  case Jakarta:
    return "Jakarta";
    break;
  case Johannesburg:
    return "Johannesburg";
    break;
  case Karachi:
    return "Karachi";
    break;
  case Khartoum:
    return "Khartoum";
    break;
  case Kinshasa:
    return "Kinshasa";
    break;
  case Kolkata:
    return "Kolkata";
    break;
  case Lagos:
    return "Lagos";
    break;
  case Lima:
    return "Lima";
    break;
  case London:
    return "London";
    break;
  case LosAngeles:
    return "LosAngeles";
    break;
  case Madrid:
    return "Madrid";
    break;
  case Manila:
    return "Manila";
    break;
  case MexicoCity:
    return "MexicoCity";
    break;
  case Miami:
    return "Miami";
    break;
  case Milan:
    return "Milan";
    break;
  case Montreal:
    return "Montreal";
    break;
  case Moscow:
    return "Moscow";
    break;
  case Mumbai:
    return "Mumbai";
    break;
  case NewYork:
    return "NewYork";
    break;
  case Osaka:
    return "Osaka";
    break;
  case Paris:
    return "Paris";
    break;
  case Riyadh:
    return "Riyadh";
    break;
  case SanFrancisco:
    return "SanFrancisco";
    break;
  case Santiago:
    return "Santiago";
    break;
  case SaoPaulo:
    return "SaoPaulo";
    break;
  case Seoul:
    return "Seoul";
    break;
  case Shanghai:
    return "Shanghai";
    break;
  case StPetersburg:
    return "StPetersburg";
    break;
  case Sydney:
    return "Sydney";
    break;
  case Taipei:
    return "Taipei";
    break;
  case Tehran:
    return "Tehran";
    break;
  case Tokyo:
    return "Tokyo";
    break;
  default:
    throw invalid_argument{"Unknown City Error."};
  }
}
string Board::toString(Color color) {
  switch (color) {
  case (Blue):
    return "Blue";
    break;
  case (Black):
    return "Black";
    break;
  case (Red):
    return "Red";
    break;
  case (Yellow):
    return "Yellow";
    break;
  default:
    throw invalid_argument{"Unknown Name Error."};
  }
}
Color Board::colorOf(City city) { return loc[city].color; }
void Board::addCure(Color color) { cures.at(color)++; }
array<int, 4> Board::getCureArray() { return cures; }

} // namespace pandemic