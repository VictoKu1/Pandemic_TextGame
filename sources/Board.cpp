#include "Board.hpp"
#include "City.hpp"
#include <ios>
#include <stdexcept>
using namespace std;
namespace pandemic {

//*Printing function implemetation for Location subclass .
ostream &operator<<(ostream &os, const Board::Location &loc) {
  return (os << "\n Research lab existance status: " << boolalpha
             << loc.laboratoryEx << noboolalpha
             << ".\n Illness type: " << Board::toString(loc.color)
             << "\n Illness level : " << to_string(loc.numOfCubes) << endl);
}

//*Function which returns a refference to the number of cubes in a cpecific city parameter.
int &Board::operator[](City city) { return loc[city].numOfCubes; }

//*Printing function implemetation .
ostream &operator<<(ostream &os, const Board &board) {
  os << "Board data :" << endl;
  for (const auto &c : board.loc) {
    os << "_________________________________________________\n"
       << "City: " << Board::toString(c.first) << c.second << endl;
  }
  os << "_________________________________________________\n"
     << "Cures found :"
     << "\n Blue: " << board.cures.at(Blue)
     << "\n Black: " << board.cures.at(Black)
     << "\n Red: " << board.cures.at(Red)
     << "\n Yellow: " << board.cures.at(Yellow) << endl;
  os << "_________________________________________________" << endl;
  return os;
}

//*Boolean method which tells if all the cubes on the board is equal to 0.
bool Board::is_clean() {
  for (auto &place : loc) {
    if (place.second.numOfCubes > 0) {
      return false;
    }
  }
  return true;
}

//*Method which tells if two of the given cities has a connection between them .
bool Board::isConnected(City from, City to) {
  return (loc[from].connections.count(to) != 0);
}

//*Boolean method which tells if a given city has a builded lab in it .
bool Board::labExists(City city) { return loc[city].laboratoryEx; }

//*Method which builds a research lab in the given city .
void Board::makeLab(City city) { loc[city].laboratoryEx = true; }

//*Method which nullifies the number of the founded cures.
void Board::remove_cures() { cures.fill(0); }

//*Method which nullifies all of the builded labs .
void Board::remove_stations() {
  for (auto &place : loc) {
    place.second.laboratoryEx = false;
  }
}

//* Static method which returns for each city enum value its relevant string value .
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
  case Washington:
    return "Washington";
    break;
  default:
    throw invalid_argument{"Unknown City Error."};
  }
}

//*Static method which returns to each given color enum value its relevant string value .
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

//*Method which returns color enum value for the given city .
Color Board::colorOf(City city) { return loc[city].color; }

//*Method which promotes the number of the founded cures.
void Board::addCure(Color color) { cures.at(color) += 1; }

//*Method which returns a reference to the array which represends a number of the founded cures for each disease.
array<int, 4> &Board::getCureArray() { return cures; }
} // namespace pandemic
