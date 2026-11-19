#pragma once
#include "Errors.hpp"
#include "Registry.hpp"
#include "Inventory.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <memory>

class Park {
  Registry<std::shared_ptr<InventoryItem>, max_cap> park_;
  std::weak_ptr<InventoryItem> focus_;
  Registry<std::string, max_cap> models_;
  double total_energy_;

  bool HasBroken(const std::string& name) {
    return name == "broken";
  }

  bool FindID(const std::string& id) {
    for (int i = 0; i < park_.Size(); ++i) {
      if (park_[i]->inventory_id() == id) {
        return 1;
      }
    }
    return 0;
  }

  int FindIndex(const std::string& id) {
      for (int i = 0; i < park_.Size(); ++i) {
          if (park_[i]->inventory_id() == id) return i;
      }
      return park_.Size();
  }

  void Inspection(const std::string& name) {
    if (HasBroken(name)) {
      throw InspectionError();
    }
    if (models_.Find(name) == models_.Size()) {
      models_.Add(name);
    }
  }

  void AddItem(std::unique_ptr<InventoryItem> item) {
    const std::string id = item->inventory_id();
    if (FindID(id)) {
      throw UniqueError();
    }
    park_.Add(std::shared_ptr<InventoryItem>(std::move(item)));
  }

 public:
  Park& operator+=(const EnergyConsumer& consumer) {
    total_energy_ += consumer.daily_energy();
    return *this;
  }

  Park() = default;

  void AddScooter(const std::string& id, const std::string& name, const double& energy,
                  const int& simple) {
    if (simple < 1 || simple > 10) {
      throw SimplicityError();
    }

    if (energy < 0) {
      throw EnergyError();
    }

    if (FindID(id)) {
      throw UniqueError();
    }

    Inspection(name);
    std::unique_ptr item = std::make_unique<Scooter>(id, name, energy, simple);
    AddItem(std::move(item));
  }

  void AddBike(const std::string& id, const std::string& name, const int& simple) {
    if (simple < 1 || simple > 10) {
      throw SimplicityError();
    }

    if (FindID(id)) {
      throw UniqueError();
    }

    Inspection(name);
    auto item = std::make_unique<Bike>(id, name, simple);
    AddItem(std::move(item));
  }

  void AddEBike(const std::string& id, const std::string& name,
                const double& energy, const int& simple) {
    if (simple < 1 || simple > 10) {
      throw SimplicityError();
    }
    if (energy < 0) {
      throw EnergyError();
    }

    if (FindID(id)) {
      throw UniqueError();
    }

    Inspection(name);
    auto item = std::make_unique<EBike>(id, name, energy, simple);
    AddItem(std::move(item));
  }

  void AddUnicycle(const std::string& id, const std::string& name, const int& simple) {
    if (simple < 1) {
      throw SimplicityError();
    }
    if (simple > 3) {
      throw UnicycleError();
    }

    if (FindID(id)) {
      throw UniqueError();
    }

    Inspection(name);
    auto item = std::make_unique<Unicycle>(id, name, simple);
    AddItem(std::move(item));
  }

  void AddHelmet(const std::string& id, const std::string& name) {
    auto item = std::make_unique<Helmet>(id, name);
    AddItem(std::move(item));
  }

  void AddDock(const std::string& id, const std::string& name, const double& energy) {
    if (energy < 0) {
      throw EnergyError();
    }

    auto item = std::make_unique<Dock>(id, name, energy);
    AddItem(std::move(item));
  }

  void PrintEnergy() {
    total_energy_ = 0.0;
    for (int i = 0; i < park_.Size(); ++i) {
      if (auto consumer = dynamic_cast<EnergyConsumer*>(park_[i].get())) {
        total_energy_ += consumer->daily_energy();
      }
    }
    std::cout << std::fixed << std::setprecision(1) << total_energy_ << "\n";
  }

  void PrintNovice() {
    for (int i = 0; i < park_.Size(); ++i) {
      if (auto transport = dynamic_cast<Transport*>(park_[i].get())) {
        if (transport->simplicity() >= 6) {
          std::cout << park_[i]->inventory_id() << " " << park_[i]->name() << "\n";
        }
      }
    }
  }

  void PrintList() {
    park_.Sort();
    for (int i = 0; i < park_.Size(); ++i) {
      std::cout << *park_[i];
    }
  }

  void SetFocus(const std::string& id) {
    int idx = FindIndex(id);
    if (idx == park_.Size()) {
      throw FocusError();
    }
    focus_ = park_[idx];
  }

  void ShowFocus() {
    if (focus_.expired()) {
      std::cout << "disintegrated from existence\n";
    } else {
      std::cout << *focus_.lock();
    }
  }

  void Remove(const std::string& id) {
    int idx = FindIndex(id);
    if (idx == park_.Size()) {
      throw RemoveError();
    }
    const std::string removed_name = park_[idx]->name();
    park_.Remove(idx);

    bool still_exists = false;
    for (int i = 0; i < park_.Size(); ++i) {
      if (park_[i]->name() == removed_name) {
        still_exists = true;
        break;
      }
    }
    if (!still_exists) {
      int removed = models_.Find(removed_name);
      if (removed != models_.Size()) {
        models_.Remove(removed);
      }
    }
  }

  void ShowModels() {
    for (int i = 0; i < models_.Size(); ++i) {
      std::cout << models_[i] << "\n";
    }
  }
};
