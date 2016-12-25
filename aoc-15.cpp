#include "aoc.h"

// Another brute force solution. The only optimization here was to advance the
// time in increments of the first disc size. Given the problem size, this
// turned out to not be needed. Runtime for part two was about 20ms.

struct disc {
  int64_t slots;
  int64_t inital;
};

bool solve(int64_t drop_time, const vector<disc>& discs) {
  ++drop_time;
  for (int i = 0; i != discs.size(); ++i) {
    if ((drop_time + discs[i].inital) % discs[i].slots) {
      return false;
    }
    ++drop_time;
  }
  return true;
}

int main() {
  vector<disc> input = {
      {13, 11}, {5, 0}, {17, 11}, {3, 0}, {7, 2}, {19, 17},
      // {11, 0},  // Uncomment for part two.
  };
  int64_t start = input[0].slots - input[0].inital - 1;
  for (int64_t i = start;; i += input[0].slots) {
    if (solve(i, input)) {
      cout << i << "\n";
      break;
    }
  }
}
