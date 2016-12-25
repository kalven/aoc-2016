#include "aoc.h"
#include "md5.cpp"

// A simple variation of part one. Here we actually needed to convert the digest
// to a hex string. Runtime for part two was about 10s.

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

    char str[33];
    for (int i = 0; i != 2016; i++) {
      for (int j = 0; j != 16; ++j) {
        int hi = digest[j] >> 4;
        int lo = digest[j] & 15;
        str[j*2+0] = (hi < 10) ? hi + '0' : hi - 10 + 'a';
        str[j*2+1] = (lo < 10) ? lo + '0' : lo - 10 + 'a';
      }
      md5_init(state);
      md5_process(state, str, 32);
      md5_done(state, digest);
    }

    for (int i = 0; i != sizeof(digest); i++) {
      nibbles[i*2+0] = digest[i] >> 4;
      nibbles[i*2+1] = digest[i] & 15;
    }
  }
};


int main() {
  key_gen kg;

  for (unsigned int i = 0; i != 30000; ++i) {
    kg.gen_one(i);
  }

  int keys = 0;
  for (auto triple : kg.triples) {
    auto nibble = triple.first;
    auto index = triple.second;

    auto qt = kg.quintuples.lower_bound({nibble, index+1});
    if (qt != kg.quintuples.end() && qt->first == nibble && qt->second <= index+1000) {
      if (++keys == 64) {
        cout << "Got key " << keys << " at " << index << "\n";
        break;
      }
    }
  }
}
