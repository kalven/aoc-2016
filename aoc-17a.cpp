#include "aoc.h"
#include "md5.cpp"

// For some reason I did DFS here. It may have been because we can then keep a
// single array to represent the current path. As we're recursing down, the path
// is updated. We keep track of the best found solution so far and abort
// searches that are longer. Runtime for this part was about 5ms.

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

int best = 9999;
string best_solution;

void recurse(char* path, int offset, int x, int y) {
  if (x == 3 && y == 3) {
    if (offset < best) {
      best = offset;
      best_solution.assign(path + 8, path + offset);
    }
    return;
  }
  if (offset > best) {
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
  char path[64] = "awrkjxxr";
  int offset = strlen(path);

  recurse(path, offset, 0, 0);
  cout << best_solution << "\n";
}
