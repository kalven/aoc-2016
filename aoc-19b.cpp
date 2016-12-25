#include "aoc.h"

#include <boost/multi_index/ranked_index.hpp>
#include <boost/multi_index_container.hpp>

// My solution from part one wouldn't work well when I had to advance iterator
// size/2 steps instead of just one.. So I reached out to boost and grabbed a
// set that allows translations between index and iterator in O(log N) time. In
// retrospect, simpler things could have been done. Runtime about 2.3s.

namespace bmi = boost::multi_index;

typedef bmi::multi_index_container<
    int, bmi::indexed_by<bmi::ranked_unique<bmi::identity<int> > > >
    int_set;

int main() {
  int input = 3014387;

  int_set state;
  for (int i = 1; i <= input; ++i) {
    state.insert(i);
  }

  size_t pos = 0;
  for (;;) {
    auto steal_pos = (pos + (state.size() / 2)) % state.size();

    state.erase(state.nth(steal_pos));
    if (steal_pos < pos) {
      --pos;
    }

    if (state.size() == 1) {
      cout << *state.begin() << "\n";
      break;
    }

    ++pos;
    if (pos >= state.size()) {
      pos = 0;
    }
  }
}
