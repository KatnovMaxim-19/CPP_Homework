#pragma once
#include "Inventory.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

const int max_cap = 250;

template<typename T, int cap>
class Registry {
  std::vector<T> registry_;
  int size_ = 0;

 public:
  T& operator[](size_t idx) {
    return registry_[idx];
  }

  int Size() const { return size_; }

  void Add(const T& item) {
    if (size_ >= cap) {
      throw RegistryError();
      return;
    }
    registry_.push_back(item);
    ++size_;
  }

  int Find(const T& item) {
    for (int i = 0; i < size_; ++i) {
      if (registry_[i] == item) {
        return i;
      }
    }
    return size_;
  }

  void Remove(int idx) {
    if (idx < 0 || idx >= size_) return;
    registry_.erase(registry_.begin() + idx);
    --size_;
  }
};

template<>
class Registry<std::shared_ptr<InventoryItem>, max_cap> {
  std::vector<std::shared_ptr<InventoryItem>> registry_;
  int size_ = 0;

 public:
  std::shared_ptr<InventoryItem>& operator[](size_t idx) {
    return registry_[idx];
  }

  int Size() const {
    return size_;
  }

  void Add(const std::shared_ptr<InventoryItem>& item) {
    if (size_ >= max_cap) {
      throw RegistryError();
      return;
    }
    registry_.push_back(item);
    ++size_;
  }

  void Sort() {
    std::sort(registry_.begin(), registry_.end(), [](const std::shared_ptr<InventoryItem>& a,
                                                     const std::shared_ptr<InventoryItem>& b) {
      return *a < *b;
    });
  }

  void Remove(int idx) {
    if (idx < 0 || idx >= size_) return;
    registry_.erase(registry_.begin() + idx);
    --size_;
  }
};
