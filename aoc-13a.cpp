#include "aoc.h"

// Another problem that calls for BFS. Very similar to part 11, just with a
// simpler state representation. Runtime about 5ms.

using point = pair<int, int>;

struct maze {
  int key;

  bool wall(int x, int y) {
    int v = x * x + 3 * x + 2 * x * y + y + y * y;
    v += key;
    return bitset<32>(v).count() & 1;
  }

  vector<point> moves(int x, int y) {
    vector<point> res;
    if (!wall(x + 1, y)) {
      res.push_back({x + 1, y});
    }
    if (x > 0 && !wall(x - 1, y)) {
      res.push_back({x - 1, y});
    }
    if (!wall(x, y + 1)) {
      res.push_back({x, y + 1});
    }
    if (y > 0 && !wall(x, y - 1)) {
      res.push_back({x, y - 1});
    }
    return res;
  }
};

int main() {
  maze mz{1358};
  point start = {1, 1};
  set<point> visited = {start};
  using state_move = pair<point, int>;
  queue<state_move> q;
  q.push({start, 0});

  while (!q.empty()) {
    state_move m = q.front();
    q.pop();
    point p = m.first;
    if (p.first == 31 && p.second == 39) {
      cout << "Reached in " << m.second << "\n";
      break;
    }

    for (point np : mz.moves(p.first, p.second)) {
      if (visited.count(np)) {
        continue;
      }
      visited.insert(np);
      q.push({np, m.second + 1});
    }
  }
}
