#include "aoc.h"

// Part 1 was fairly straightforward. Just a matter of parsing the input and
// executing instructions.
// 
// Part 2 hinted that one shouldn't try to keep the entire decompressed output
// in memory. The first decompression function luckily turned out to be easy to
// tweak. Runtime for part 2 was about 1m40s which meant no further optimization
// was needed.

pair<int, int> parse_marker(const string& input, int offset) {
  int x, y;
  check(sscanf(input.c_str() + offset, "(%dx%d)", &x, &y) == 2, "malformed");
  return {x, y};
}

string decompress(const string& input) {
  string output;

  for (int i = 0; i != input.size(); ++i) {
    if (input[i] == '(') {
      auto marker = parse_marker(input, i);
      while (input[i] != ')') {
        i++;
      }
      i++;

      for (int j = 0; j != marker.second; ++j) {
        output += input.substr(i, marker.first);
      }
      i += marker.first - 1;
    } else {
      if (input[i] != '\n') {
        output += input[i];
      }
    }
  }

  return output;
}

size_t decompress2(const string& input) {
  size_t size = 0;

  for (int i = 0; i != input.size(); ++i) {
    if (input[i] == '(') {
      string fragment;
      auto marker = parse_marker(input, i);
      while (input[i] != ')') {
        i++;
      }
      i++;

      for (int j = 0; j != marker.second; ++j) {
        fragment += input.substr(i, marker.first);
      }
      i += marker.first - 1;

      size += decompress2(fragment);

    } else {
      if (input[i] != '\n') {
        size++;
      }
    }
  }

  return size;
}

int main() {
  string input = get_file_contents("aoc-9.txt");

  cout << decompress(input).size() << "\n";
  cout << decompress2(input) << "\n";
}
