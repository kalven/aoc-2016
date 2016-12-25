#include "aoc.h"

// An unusually simple problem. Just a matter of getting the conditions
// right. 2ms runtime for part 1, 400ms for part 2. Unfortunately, the problem
// was too small to need any forms of optimizations for part 2. This was a bit
// of a bummer.

string generate(const string& input) {
  string result;
  result.resize(input.size());

  for (int i = 0; i != input.size(); ++i) {
    char l = (i == 0) ? '.' : input[i - 1];
    char c = input[i];
    char r = (i == input.size() - 1) ? '.' : input[i + 1];

    if (l == '^' && c == '^' && r == '.') {
      result[i] = '^';
      continue;
    }
    if (l == '.' && c == '^' && r == '^') {
      result[i] = '^';
      continue;
    }
    if (l == '^' && c == '.' && r == '.') {
      result[i] = '^';
      continue;
    }
    if (l == '.' && c == '.' && r == '^') {
      result[i] = '^';
      continue;
    }
    result[i] = '.';
  }

  return result;
}

int main() {
  const char input[] =
      "^^^^......^...^..^....^^^.^^^.^.^^^^^^..^...^^...^^^.^^....^..^^^.^.^^.."
      ".^.^...^^.^^^.^^^^.^^.^..^.^";

  int input_size = 40;
  // int input_size = 400000; // For part 2.

  vector<string> m = {input};
  for (int i = 0; i != input_size - 1; ++i) {
    m.push_back(generate(m.back()));
  }

  int safe = 0;
  for (auto& line : m) {
    for (char c : line) {
      safe += (c == '.');
    }
  }

  cout << safe << "\n";
}
