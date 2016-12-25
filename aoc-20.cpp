#include "aoc.h"

#include <boost/icl/interval_set.hpp>

// For the second time, I reached for boost. This turned out to be a very simple
// problem when you have access to an interval set. The default interval set
// from boost will merge intervals. Runtime 3ms.

int main() {
  vector<pair<int64_t, int64_t>> input;

  for(const string& line : get_file_lines("aoc-20.txt")) {
    pair<int64_t, int64_t> p;
    check (sscanf(line.c_str(), "%lld-%lld", &p.first, &p.second) == 2, "parse");
    input.push_back(p);
  }

  boost::icl::interval_set<int64_t> is;
  for (auto p : input) {
    is.insert({p.first, p.second});
  }

  int64_t blacklisted = 0;
  for (auto x : is) {
    blacklisted += (x.upper() - x.lower()) + 1;
  }
  cout << is.begin()->upper() + 1 << "\n";
  cout << (1ll << 32) - blacklisted << "\n";
}
