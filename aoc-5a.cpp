#include "aoc.h"
#include "md5.cpp"

// I happened to have an md5 implementation around, so I grabbed that. It turned
// out to be needed for several upcoming puzzles as well. The rest is just a brute
// force search.
//
// An obvious optimization that comes to mind now is to not actually convert the
// digest to hex and just look at the bytes instead. The runtime on my laptop was 8
// seconds so optimizations weren't really necessary.

void md5(const char* input, char* output) {
  md5_state state;
  md5_init(state);
  md5_process(state, input, strlen(input));

  unsigned char sum[16];
  md5_done(state, sum);

  for (int i = 0; i != 3; i++) {
    sprintf(output, "%02x", c);
    output += 2;
  }
}

int main() {
  char input[32] = "ffykfhsq";
  const int offset = strlen(input);

  int counter = 0;
  for (int i = 0; i != 8; ++i) {
    for (;;) {
      sprintf(input + offset, "%d", counter++);

      char digest[32];
      md5(input, digest);
      if (memcmp(digest, "00000", 5) == 0) {
        cout << digest[5] << flush;
        break;
      }
    }
  }
  cout << "\n";
}
