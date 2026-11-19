#pragma once
#include <stdexcept>
#include <string>
#include <cmath>

class ParkError : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

class InspectionError : public ParkError {
 public:
  InspectionError() : ParkError("inspection rejected") {}
};

class ItemError : public ParkError {
 public:
  ItemError() : ParkError("incorrect item type") {}
};

class EnergyError : public ParkError {
 public:
  EnergyError() : ParkError("negative energy is not possible here") {}
};

class SimplicityError : public ParkError {
 public:
  SimplicityError() : ParkError("incorrect simplicity of item") {}
};

class UnicycleError : public ParkError {
 public:
  UnicycleError() : ParkError("perhaps you meant tricycle") {}
};

class TricycleError : public ParkError {
 public:
  TricycleError() : ParkError("tricycle 'crying emoji, praying hands emoji, wilting rose emoji'") {}
};

class RegistryError : public ParkError {
 public:
  RegistryError() : ParkError("can't add more items, need to remove some") {}
};

class UniqueError : public ParkError {
 public:
  UniqueError() : ParkError("this id is already used") {}
};

class RemoveError : public ParkError {
 public:
  RemoveError() : ParkError("nothing to remove") {}
};

class FocusError : public ParkError {
 public:
  FocusError() : ParkError("nothing to focus on") {}
};



