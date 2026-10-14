#include <cstring>
#include <iostream>

using CommandFunc = void (*)(int& balance, int k);

struct Command {
  const char* name;
  CommandFunc func;
};

void Deposit(int& balance, int k) {
  if (k > 0) {
    balance += k;
  } else {
    std::cout << "error\n";
  }
}

void Withdraw(int& balance, int k) {
  if (k > 0 && k <= balance) {
    balance -= k;
  } else {
    std::cout << "error\n";
  }
}

void Balance(int& balance, int) {
  std::cout << balance << "\n";
}

void Reset(int& balance, int) {
  balance = 0;
}

void Double(int& balance, int) {
  balance *= 2;
}

int main() {
  const Command commands[] = {
      {"deposit", Deposit},   {"withdraw", Withdraw},
      {"balance", Balance},   {"reset", Reset},
      {"double", Double},
  };
  const int count = sizeof(commands) / sizeof(commands[0]);

  int balance = 0;
  char cmd[64];

  while (std::cin >> cmd) {
    if (std::strcmp(cmd, "stop") == 0) {
      break;
    }

    for (int i = 0; i < count; ++i) {
      if (std::strcmp(cmd, commands[i].name) == 0) {
        int k = 0;
        std::cin >> k;
        commands[i].func(balance, k);
        break;
      }
    }
  }

  return 0;
}
