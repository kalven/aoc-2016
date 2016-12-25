#include "aoc.h"

// Just parsing input and executing instructions. Using a set to keep track of
// visited positions.

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int main() {
  int x = 0, y = 0;
  int facing = 0;
  bool visited_twice = false;

  set<pair<int, int>> visited = {{x, y}};

  string input = get_file_contents("aoc-1.txt");
  for (string c : split(input, ',')) {
    c = trim(c);

    char dir;
    int dist;
    check(sscanf(c.c_str(), "%c%d", &dir, &dist) == 2, "parse");

    if (dir == 'L') {
      --facing;
    } else {
      ++facing;
    }
    facing = (facing + 4) % 4;

    for (int i = 0; i != dist; ++i) {
      x += dx[facing];
      y += dy[facing];

      if (!visited_twice && visited.count({x, y})) {
        cout << "visited twice: " << abs(x) + abs(y) << "\n";
        visited_twice = true;
      }
      visited.insert({x, y});
    }
  }
  cout << "total: " << abs(x) + abs(y) << "\n";
}
