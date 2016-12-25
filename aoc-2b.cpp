#include "aoc.h"

/*
  Like 2a, but changed board representation and move function.
*/

int main() {
  int x = 0, y = 2;
  const char pad[5][5] = {{'_', '_', '1', '_', '_'},
                          {'_', '2', '3', '4', '_'},
                          {'5', '6', '7', '8', '9'},
                          {'_', 'A', 'B', 'C', '_'},
                          {'_', '_', 'D', '_', '_'}};

  auto move = [&](int dx, int dy) {
    int nx = x + dx;
    int ny = y + dy;
    if (nx != -1 && nx != 5 && ny != -1 && ny != 5 && pad[ny][nx] != '_') {
      x = nx;
      y = ny;
    }
  };

  auto lines = get_file_lines("aoc-2a.txt");
  for (const string& line : lines) {
    for (char c : line) {
      switch (c) {
        case 'U':
          move(0, -1);
          break;
        case 'D':
          move(0, +1);
          break;
        case 'R':
          move(+1, 0);
          break;
        case 'L':
          move(-1, 0);
          break;
      }
    }
    cout << pad[y][x];
  }
  cout << "\n";
}
