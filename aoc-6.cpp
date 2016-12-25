#include "aoc.h"

// Just a simple case of running over the input and keeping track of character
// occurrences.

pair<char, char> least_and_most_common(const map<char, int>& hist) {
  using p = pair<char, int>;
  auto i = minmax_element(hist.begin(), hist.end(),
                          [](p l, p r) { return l.second < r.second; });
  return {i.first->first, i.second->first};
}

int main() {
  map<int, map<char, int>> hist;

  vector<string> input = get_file_lines("aoc-6.txt");
  for (const string& msg : input) {
    for (int i = 0; i != msg.size(); ++i) {
      hist[i][msg[i]]++;
    }
  }

  string answer1, answer2;
  for (const auto& p : hist) {
    auto pp = least_and_most_common(p.second);
    answer1 += pp.second;
    answer2 += pp.first;
  }
  cout << "answer1: " << answer1 << "\n"
       << "answer2: " << answer2 << "\n";
}
