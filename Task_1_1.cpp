#include <iomanip>
#include <iostream>

struct MaxMin {
  int max;
  int min;
};

double AvgTemp(const int* temp, int n) {
  long long summ = 0;

  for (int i = 0; i < n; ++i) {
    summ += temp[i];
  }
  return static_cast<double>(summ) / n;
}

MaxMin MaxMinDays(const int* temp, int n) {
  MaxMin res;
  res.min = temp[0];
  res.max = temp[0];

  for (int i = 1; i < n; ++i) {
    if (temp[i] < res.min) {
      res.min = temp[i];
    }
    if (temp[i] > res.max) {
      res.max = temp[i];
    }
  }
  return res;
}

int ColdDays(const int* temp, int n) {
  int count = 0;

  for (int i = 0; i < n; i++) {
    if (temp[i] < 0) {
      count++;
    }
  }
  return count;
}

int main() {
  int n = 0;
  std::cin >> n;

  int* temp = new int[n];

  for (int i = 0; i < n; i++) {
    std::cin >> temp[i];
  }

  const MaxMin two_days = MaxMinDays(temp, n);

  std::cout << std::fixed << std::setprecision(1) << AvgTemp(temp, n) << "\n";
  std::cout << two_days.min << " " << two_days.max << "\n";
  std::cout << ColdDays(temp, n) << "\n";

  delete[] temp;
  return 0;
}
