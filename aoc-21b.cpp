#include "aoc.h"

// Doing the operations from part one in reverse. The only part here that
// requires some extra care is the 'rotate based on'-instruction. I ended up
// mapping all cases (that's the rmap array).

int main() {
  vector<string> input = get_file_lines("aoc-21.txt");
  reverse(input.begin(), input.end());

  string str = "fbgdceah";

  int rmap[] = {1, 1, 6, 2, 7, 3, 0, 4};

  for (string line : input) {
    char letter_a, letter_b;
    int position_a, position_b;
    int rotation;

    const char* l = line.c_str();
    if (sscanf(l, "swap position %d with position %d", &position_a,
               &position_b) == 2) {
      swap(str.at(position_a), str.at(position_b));
    } else if (sscanf(l, "swap letter %c with letter %c", &letter_a,
                      &letter_b) == 2) {
      replace(str.begin(), str.end(), letter_a, '\0');
      replace(str.begin(), str.end(), letter_b, letter_a);
      replace(str.begin(), str.end(), '\0', letter_b);
    } else if (sscanf(l, "reverse positions %d through %d", &position_a,
                      &position_b) == 2) {
      reverse(str.begin() + position_a, str.begin() + position_b + 1);
    } else if (sscanf(l, "rotate left %d step", &rotation) == 1) {
      rotate(str.begin(), str.end() - rotation, str.end());
    } else if (sscanf(l, "rotate right %d step", &rotation) == 1) {
      rotate(str.begin(), str.begin() + rotation, str.end());
    } else if (sscanf(l, "move position %d to position %d", &position_a,
                      &position_b)) {
      char c = str.at(position_b);
      str.erase(str.begin() + position_b);
      str.insert(str.begin() + position_a, c);
    } else if (sscanf(l, "rotate based on position of letter %c", &letter_a) ==
               1) {
      auto pos = str.find(letter_a);
      rotate(str.begin(), str.begin() + rmap[pos], str.end());
    } else {
      check(false, "parse: " + line);
    }
  }

  cout << str << "\n";
}
