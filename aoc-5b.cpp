#include "aoc.h"
#include "md5.cpp"

// A simple variation on the first part. I ended up using a bitset to represent
// the set digits. That made it easy to check when all digits have been
// found. Runtime was about 40 seconds.

void md5(const char* input, char* output) {
  md5_state state;
  md5_init(state);
  md5_process(state, input, strlen(input));

  unsigned char sum[16];
  md5_done(state, sum);

  for (unsigned char c : sum) {
    sprintf(output, "%02x", c);
    output += 2;
  }
}

int main() {
  char input[32] = "ffykfhsq";
  const int offset = strlen(input);

  int filled = 0;
  int counter = 0;

  char output[9] = "________";

  for (int counter = 0;; counter++) {
    sprintf(input + offset, "%d", counter);

    char digest[32];
    md5(input, digest);
    if (memcmp(digest, "00000", 5) == 0) {

      char posc = digest[5];
      if (posc < '0' || posc > '7') {
        continue;
      }
      int pos = posc - '0';

      if (filled & (1 << pos)) {
        continue;
      }

      output[pos] = digest[6];
      cout << output << "\n";

      filled |= (1 << pos);
      if (filled == 255) {
        break;
      }
    }
  }
  cout << "\n";
}
