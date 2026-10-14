#include <cstring>
#include <iostream>

const int cRows = 5;
const int cCols = 10;

void Clear(char board[cRows][cCols]) {
  for (int row = 0; row < cRows; ++row) {
    for (int col = 0; col < cCols; ++col) {
      board[row][col] = ' ';
    }
  }
}

bool Put(char board[cRows][cCols], int col, int row, char symbol) {
  if (col < 0 || col >= cCols || row < 0 || row >= cRows) {
    return false;
  }
  board[row][col] = symbol;
  return true;
}

bool Text(char board[cRows][cCols], int col, int row, const char* word) {
  const int wordLength = static_cast<int>(std::strlen(word));

  if (row < 0 || row >= cRows) {
    return false;
  }
  if (col < 0 || col + wordLength > cCols) {
    return false;
  }

  for (int i = 0; i < wordLength; ++i) {
    board[row][col + i] = word[i];
  }
  return true;
}

void Print(const char board[cRows][cCols]) {
  for (int row = 0; row < cRows; ++row) {
    for (int col = 0; col < cCols; ++col) {
      std::cout << board[row][col];
    }
    std::cout << "\n";
  }
}

int main() {
  char board[cRows][cCols];
  Clear(board);

  char command[64];
  while (std::cin >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }

    if (std::strcmp(command, "clear") == 0) {
      Clear(board);
    } else if (std::strcmp(command, "print") == 0) {
      Print(board);
    } else if (std::strcmp(command, "put") == 0) {
      int col = 0;
      int row = 0;
      char symbol = ' ';

      std::cin >> col >> row >> symbol;
      if (!Put(board, col, row, symbol)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int col = 0;
      int row = 0;
      char word[64];

      std::cin >> col >> row >> word;

      if (!Text(board, col, row, word)) {
        std::cout << "error\n";
      }
    } else {
      std::cout << "error\n";
    }
  }

  return 0;
}
