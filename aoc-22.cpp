#include "aoc.h"

// The less said about this day the better. Part 1 was a simple O(n^2)
// scan. Part 2 was basically solved by hand, with some assistance from the
// program. I printed the input data and the moves that had to be made. I then
// wrote some helper functions to perform these moves and verify that only legal
// moves were made. It was then just a matter of adding some moves, checking the
// output and repeating until the problem had been solved.
//
// Once again: this solution is made specifically for *my* problem input.

struct item {
  char cid1, cid2;
  int id1, id2;

  string fs;
  int size, used, avail, pct;
  bool target = false;
};

int main() {
  vector<string> input = get_file_lines("aoc-22.txt");

  using xy = pair<int, int>;

  map<pair<int, int>, item> items;
  for (const string& line : input) {
    item i;
    if (sscanf(line.c_str(), "/dev/grid/node-%c%d-%c%d %dT %dT %dT %d%%",
               &i.cid1, &i.id1, &i.cid2, &i.id2, &i.size, &i.used, &i.avail,
               &i.pct) == 8) {
      if (i.id1 == 35 && i.id2 == 0) {
        i.target = true;
      }
      items[{i.id1, i.id2}] = i;
    }
  }

  int viable = 0;
  for (const auto& p1 : items) {
    for (const auto& p2 : items) {
      if (p1.first != p2.first &&
          p1.second.used != 0 &&
          p1.second.used <= p2.second.avail) {
        ++viable;
      }
    }
  }
  cout << viable << "\n";

  auto up = [](xy p) {
    if (p.second > 0) {
      return xy{p.first, p.second - 1};
    }
  };
  auto down = [](xy p) {
    if (p.second < 29) {
      return xy{p.first, p.second + 1};
    }
  };
  auto left = [](xy p) {
    if (p.first > 0) {
      return xy{p.first - 1, p.second};
    }
  };
  auto right = [](xy p) {
    if (p.first < 35) {
      return xy{p.first + 1, p.second};
    }
  };

  auto movez = [&](auto dir, xy& fs) {
    if (dir(fs) == fs) {
      return false;
    }
    if (items[dir(fs)].used <= items[fs].size) {
      swap(items[dir(fs)].used, items[fs].used);
      swap(items[dir(fs)].target, items[fs].target);
      fs = dir(fs);
      return true;
    }
    return false;
  };

  auto cycle = [&](auto& ms, xy& fs) {
    ms += movez(down, fs);
    ms += movez(left, fs);
    ms += movez(left, fs);
    ms += movez(up, fs);
    ms += movez(right, fs);
  };

  int moves = 0;
  xy freespace = {35, 27};

  for (int i = 0; i != 20; ++i) {
    moves += movez(up, freespace);
  }
  for (int i = 0; i != 34; ++i) {
    moves += movez(left, freespace);
  }
  for (int i = 0; i != 40; ++i) {
    moves += movez(up, freespace);
  }
  for (int i = 0; i != 34; ++i) {
    moves += movez(right, freespace);
  }
  for (int i = 0; i != 34; ++i) {
    cycle(moves, freespace);
  }

  for (int y = 0; y != 30; y++) {
    for (int x = 0; x != 36; x++) {
      bool fz = items[{x, y}].used == 0;
      bool target = items[{x, y}].target;

      if (fz) {
        printf("_ ");
      } else if (target) {
        printf("$ ");
      } else {
        printf("; ");
      }
    }
    printf("\n");
  }

  cout << moves << "\n";
}
