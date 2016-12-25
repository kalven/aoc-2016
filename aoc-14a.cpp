#include "aoc.h"
#include "md5.cpp"

// Another MD5 problem. I created a function to generate the digest for a single
// iteration and extract tripples and quintuples from it. Instead of converting
// the digest to a string, the nibbles were just extracted.
// 
// This function was run for the first 100k candidates. The quintuples were kept
// in a set sorted by {hex-digit, index}. I could then iterate the tripples and
// do efficient lookups in the set of quintuples. Runtime about 6ms.

struct key_gen {
  // Key: hex-digit, index
  using key = pair<unsigned char, unsigned int>;

  vector<key> triples;
  set<key> quintuples;

  void gen_one(unsigned int counter) {
    unsigned char nibbles[32];
    md5_key(counter, nibbles);
    for (int i = 0; i != sizeof(nibbles)-2; i++) {
      if (nibbles[i] == nibbles[i+1] &&
          nibbles[i] == nibbles[i+2]) {
        triples.push_back({nibbles[i], counter});
        break;
      }
    }
    for (int i = 0; i != sizeof(nibbles)-4; i++) {
      if (nibbles[i] == nibbles[i+1] &&
          nibbles[i] == nibbles[i+2] &&
          nibbles[i] == nibbles[i+3] &&
          nibbles[i] == nibbles[i+4]) {
        quintuples.insert({nibbles[i], counter});
      }
    }
  }

  void md5_key(unsigned int counter, unsigned char* nibbles) {
    char salt[32] = "yjdafjpo";
    const int offset = strlen(salt);

    sprintf(salt + offset, "%d", counter);
    md5_state state;
    md5_init(state);
    md5_process(state, salt, strlen(salt));

    unsigned char digest[16];
    md5_done(state, digest);
    for (int i = 0; i != sizeof(digest); i++) {
      nibbles[i*2+0] = digest[i] >> 4;
      nibbles[i*2+1] = digest[i] & 15;
    }
  }
};

int main() {
  key_gen kg;

  for (unsigned int i = 0; i != 100000; ++i) {
    kg.gen_one(i);
  }

  int keys = 0;
  unsigned int last_key = 0;
  for (auto triple : kg.triples) {
    auto nibble = triple.first;
    auto index = triple.second;
    if (index == last_key) {
      continue;
    }

    auto qt = kg.quintuples.lower_bound({nibble, index+1});
    if (qt != kg.quintuples.end() && qt->first == nibble && qt->second <= index+1000) {
      last_key = index;
      if (++keys == 64) {
        cout << "Got key " << keys << " at " << index << ", " << qt->second << "\n";
        break;
      }
    }
  }
}
