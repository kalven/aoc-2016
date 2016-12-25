#include "aoc.h"

// I used std::rotate to do row rotations. Column rotation was implemented by
// transposing it to a row, rotating that and then converting it back. Maybe
// crude, but it worked well.
//
// Part two was funny - just a matter of printing out the final state and
// looking at it.

void rotate_dist(char* b, char* e, int dist) {
  rotate(b, b + (e - b - dist), e);
}

int main() {
  const int width = 50;
  const int height = 6;

  char m[width * height];
  fill(begin(m), end(m), ' ');

  vector<string> input = get_file_lines("aoc-8.txt");

  for (const string& line : input) {
    int w, h, r, c;
    if (sscanf(line.c_str(), "rect %dx%d", &w, &h) == 2) {
      for (int y = 0; y != h; ++y) {
        auto row_start = m + (y * width);
        fill(row_start, row_start + w, '#');
      }
    } else if (sscanf(line.c_str(), "rotate row y=%d by %d", &c, &r) == 2) {
      r = r % width;
      auto row_start = m + (c * width);
      rotate_dist(row_start, row_start + width, r);
    } else if (sscanf(line.c_str(), "rotate column x=%d by %d", &c, &r) == 2) {
      r = r % height;

      char xposed[height];
      for (int i = 0; i != height; ++i) {
        xposed[i] = m[(i * width) + c];
      }
      rotate_dist(xposed, xposed + height, r);
      for (int i = 0; i != height; ++i) {
        m[(i * width) + c] = xposed[i];
      }
    }
  }

  for (int y = 0; y != height; ++y) {
    cout.write(m + (y * width), width) << "\n";
  }
  cout << "\n";

  cout << count(begin(m), end(m), '#') << "\n";
}
