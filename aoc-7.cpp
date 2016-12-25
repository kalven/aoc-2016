#include "aoc.h"

// A bunch of annoying string processing. I wasted some time on the incorrect
// assumption that there would only be one hypernet sequence per address.
//
// For the second part I created sets of all found ABAs (inside and outside of
// hypernet sequences). This avoided an O(N^2) scans of the input. Given the
// relatively small size of the input, that optimization probably wasn't needed.

bool is_abba(const string& s, int i) {
  check(i + 3 < s.size(), "size fail");
  return s[i] != s[i + 1] && s[i] == s[i + 3] && s[i + 1] == s[i + 2];
}

bool supports_tls(const string& ip) {
  bool has_abba = false;
  bool in_hypernet = false;

  for(size_t i = 0; (i+3) < ip.size(); ++i) {
    if (ip[i] == '[') {
      check(in_hypernet == false, "state fail #1");
      in_hypernet = true;
      continue;
    }
    if (ip[i] == ']') {
      check(in_hypernet, "state fail #2");
      in_hypernet = false;
      continue;
    }

    if (is_abba(ip, i)) {
      if (in_hypernet) {
        return false;
      }
      has_abba = true;
    }
  }

  return has_abba;
}

using abap = pair<char, char>;
bool is_aba(const string& s, int i, abap& out) {
  check(i + 2 < s.size(), "size fail");
  if (s[i] != s[i+1] && s[i] == s[i+2]) {
    out.first = s[i];
    out.second = s[i+1];
    return true;
  }
  return false;
}

bool supports_ssl(const string& ip) {
  bool in_hypernet = false;

  set<abap> outer;
  set<abap> inner;

  for(size_t i = 0; (i+2) < ip.size(); ++i) {
    if (ip[i] == '[') {
      check(in_hypernet == false, "state fail #1");
      in_hypernet = true;
      continue;
    }
    if (ip[i] == ']') {
      check(in_hypernet, "state fail #2");
      in_hypernet = false;
      continue;
    }

    abap aba;
    if (is_aba(ip, i, aba)) {
      if (in_hypernet) {
        inner.insert(aba);
      } else {
        outer.insert(aba);
      }
    }
  }

  for (const auto& outer_aba : outer) {
    abap inner_aba = {outer_aba.second, outer_aba.first};
    if (inner.count(inner_aba)) {
      return true;
    }
  }

  return false;
}

int main() {
  int tls_count = 0;
  int ssl_count = 0;
  for (string ip : get_file_lines("aoc-7.txt")) {
    tls_count += supports_tls(ip);
    ssl_count += supports_ssl(ip);
  }
  cout << "supports tls: " << tls_count << "\n";
  cout << "supports ssl: " << ssl_count << "\n";
}
