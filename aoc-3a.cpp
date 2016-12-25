#include "aoc.h"

// Yes, I happened to grab vector and I'm using sort on it. These sort of things
// happen when optimizing for programming time.

int main() {
  ifstream in("aoc-3.txt");
  int a, b, c, possible = 0;
  while (in >> a >> b >> c) {
    vector<int> v = {a, b, c};
    sort(v.begin(), v.end());
    if (v[0] + v[1] > v[2]) {
      ++possible;
    }
  }
  cout << possible << "\n";
}
