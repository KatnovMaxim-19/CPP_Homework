#pragma once
#include <iostream>
#include <string>
#include <vector>

class InventoryItem {
 protected:
  std::string inventory_id_;
  std::string name_;
 public:
  bool operator<(const InventoryItem& other) const {
    return inventory_id() < other.inventory_id();
  }

  InventoryItem(std::string id, std::string name)
  : inventory_id_(id), name_(name) {}
  virtual ~InventoryItem() = default;

  virtual std::string inventory_id() const = 0;
  virtual std::string name() const = 0;
  virtual void describe (std::ostream& stream) const = 0;
};

inline std::ostream& operator<<(std::ostream& stream, const InventoryItem& item) {
  item.describe(stream);
  return stream;
}

class EnergyConsumer {
 protected:
  double daily_energy_;
 public:
  EnergyConsumer(double energy) : daily_energy_(energy) {}
  virtual double daily_energy() const = 0;
};

struct ModelSpec {
  std::string model_name;
};

class Transport : public InventoryItem {
 protected:
  int simplicity_;
 public:
  Transport(std::string id, std::string name, int simplicity)
      : InventoryItem(id, name), simplicity_(simplicity) {}
  virtual int simplicity() const = 0;
  void describe(std::ostream& stream) const override{
    stream << inventory_id_ << " " << name_ << "\n";
  }
};

class Scooter : public Transport, public EnergyConsumer {
 public:
  Scooter(std::string id, std::string name, double energy, int score)
      : Transport(id, name, score), EnergyConsumer(energy) {}

  std::string inventory_id() const override { return inventory_id_; }
  std::string name() const override { return name_; }
  int simplicity() const override { return simplicity_; }
  double daily_energy() const override { return daily_energy_; }
};

class Bike : public Transport {
 public:
  Bike(std::string id, std::string name, int score)
      : Transport(id, name, score) {}

  std::string inventory_id() const override { return inventory_id_; }
  std::string name() const override { return name_; }
  int simplicity() const override { return simplicity_; }
};

class EBike : public Transport, public EnergyConsumer {
 public:
  EBike(std::string id, std::string name, double energy, int score)
      : Transport(id, name, score), EnergyConsumer(energy) {}

  std::string inventory_id() const override { return inventory_id_; }
  std::string name() const override { return name_; }
  int simplicity() const override { return simplicity_; }
  double daily_energy() const override { return daily_energy_; }
};

class Helmet : public InventoryItem {
 public:
  Helmet(std::string id, std::string name) : InventoryItem(id, name) {}

  std::string inventory_id() const override { return inventory_id_; }
  std::string name() const override { return name_; }
  void describe(std::ostream& stream) const override{
    stream << inventory_id_ << " " << name_ << "\n";
  }
};

class Dock : public InventoryItem, public EnergyConsumer {
 public:
  Dock(std::string id, std::string name, double energy)
      : InventoryItem(id, name), EnergyConsumer(energy) {}

  std::string inventory_id() const override { return inventory_id_; }
  std::string name() const override { return name_; }
  double daily_energy() const override { return daily_energy_; }
  void describe(std::ostream& stream) const override{
    stream << inventory_id_ << " " << name_ << "\n";
  }
};

class Unicycle : public Transport {
 public:
  Unicycle(std::string id, std::string name, int score)
      : Transport(id, name, score) {}

  std::string inventory_id() const override { return inventory_id_; }
  std::string name() const override { return name_; }
  int simplicity() const override { return simplicity_; }
};
