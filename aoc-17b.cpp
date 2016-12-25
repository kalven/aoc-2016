#include "aoc.h"
#include "md5.cpp"

// A simple modification of part one. The space was fortunately small enough
// that we didn't run out of stack space. 30ms runtime.

struct doors {
  enum dir { up, down, left, right };
  bool door[4];
};

md5_state md5;

doors find_doors(const char* input, int size) {
  unsigned char digest[16];

  md5_init(md5);
  md5_process(md5, input, size);
  md5_done(md5, digest);

  return {
      (digest[0] >> 4) > 10, (digest[0] & 15) > 10, (digest[1] >> 4) > 10,
      (digest[1] & 15) > 10,
  };
}

doors filter_doors(doors d, int x, int y) {
  return {d.door[0] && y > 0, d.door[1] && y < 3, d.door[2] && x > 0,
          d.door[3] && x < 3};
}

int best = 0;

void recurse(char* path, int offset, int x, int y) {
  if (x == 3 && y == 3) {
    if (offset > best) {
      best = offset;
    }
    return;
  }

  doors d = find_doors(path, offset);
  d = filter_doors(d, x, y);

  if (d.door[doors::down]) {
    path[offset] = 'D';
    recurse(path, offset + 1, x, y + 1);
  }
  if (d.door[doors::right]) {
    path[offset] = 'R';
    recurse(path, offset + 1, x + 1, y);
  }
  if (d.door[doors::left]) {
    path[offset] = 'L';
    recurse(path, offset + 1, x - 1, y);
  }
  if (d.door[doors::up]) {
    path[offset] = 'U';
    recurse(path, offset + 1, x, y - 1);
  }
}

int main() {
  char path[8192] = "awrkjxxr";
  int offset = strlen(path);

  recurse(path, offset, 0, 0);
  cout << best - 8 << "\n";
}
