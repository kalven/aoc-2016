#include "aoc.h"

// Nothing particurlarly interesting here either. Parsing and executing
// commands. The move function takes care of keeping the position within the
// bounds.

void move(int& v, int diff) {
  v += diff;
  if (v == -1) {
    v = 0;
  } else if (v == 3) {
    v = 2;
  }
}

int main() {
  int x = 1, y = 1;

  const int pad[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  auto lines = get_file_lines("aoc-2.txt");
  for (const string& line : lines) {
    for (char c : line) {
      switch (c) {
        case 'U':
          move(y, -1);
          break;
        case 'D':
          move(y, +1);
          break;
        case 'R':
          move(x, +1);
          break;
        case 'L':
          move(x, -1);
          break;
      }
    }
    cout << pad[y][x];
  }
  cout << "\n";
}
