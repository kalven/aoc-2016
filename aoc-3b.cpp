#include "aoc.h"

// Slight tweak of part one, now reading 3x3 sides at once.

int main() {
  ifstream in("aoc-3.txt");
  int a1, a2, a3, b1, b2, b3, c1, c2, c3, possible = 0;
  while (in >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >> a3 >> b3 >> c3) {
    auto check = [&](int x1, int x2, int x3) {
      vector<int> v = {x1, x2, x3};
      sort(v.begin(), v.end());
      if (v[0] + v[1] > v[2]) {
        ++possible;
      }
    };
    check(a1, a2, a3);
    check(b1, b2, b3);
    check(c1, c2, c3);
  }
  cout << possible << "\n";
}
