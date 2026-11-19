#include "Errors.hpp"
#include "Registry.hpp"
#include "Inventory.hpp"
#include "Service.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <memory>

int main() {
  Park park;
  std::string line;

  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    std::string command;
    ss >> command;
    if (command.empty()) {
      continue;
    }

    try {
      if (command == "add") {
        std::string type;
        ss >> type;
        std::string id, name;

        if (type == "scooter") {
          double energy;
          int score;
          ss >> id >> name >> energy >> score;
          park.AddScooter(id, name, energy, score);
        } else if (type == "bike") {
          int score;
          ss >> id >> name >> score;
          park.AddBike(id, name, score);
        } else if (type == "ebike") {
          double energy;
          int score;
          ss >> id >> name >> energy >> score;
          park.AddEBike(id, name, energy, score);
        } else if (type == "helmet") {
          ss >> id >> name;
          park.AddHelmet(id, name);
        } else if (type == "dock") {
          double energy;
          ss >> id >> name >> energy;
          park.AddDock(id, name, energy);
        } else if (type == "unicycle") {
          int score;
          ss >> id >> name >> score;
          park.AddUnicycle(id, name, score);
        }
          else if (type == "tricycle") {
            throw TricycleError(); // простите я не хотел throw в main но ЭТО надо было тут
        } else {
          throw ItemError();
        }
      } else if (command == "energy") {
        park.PrintEnergy();
      } else if (command == "novice") {
        park.PrintNovice();
      } else if (command == "list") {
        park.PrintList();
      } else if (command == "models") {
        park.ShowModels();
      } else if (command== "focus") {
        std::string id;
        ss >> id;
        park.SetFocus(id);
      } else if (command == "show_focus") {
        park.ShowFocus();
      } else if (command == "remove") {
        std::string id;
        ss >> id;
        park.Remove(id);
      } else if (command == "quit") {
        break;
      } else {
        throw ItemError();
      }
    } catch (const ParkError& e) {
      std::cout << "error: " << e.what() << "\n";
    }
  }
  return 0;
}


