#include "aoc.h"

// This wasn't a particurlarly good day for me. I ended up using a map<position,
// presents> to keep track of the state. The problem didn't call for keeping
// track of present count, but whatever. Runtime about 1.2s.
//
// A later learned that this is called the Josephus problem. There's a nice
// Numberphile episode on it: https://www.youtube.com/watch?v=uCsD3ZGzMgE

int main() {
  int input = 3014387;

  map<int, int> state;
  for (int i = 1; i <= input; ++i) {
    state[i] = 1;
  }

  auto i = state.begin();
  for (;;) {
    auto n = next(i);
    if (n == state.end()) {
      n = state.begin();
    }

    if (i == n) {
      cout << i->first << "\n";
      break;
    }

    i->second += n->second;
    state.erase(n);
    if (++i == state.end()) {
      i = state.begin();
    }
  }
}
