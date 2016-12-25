#include "aoc.h"

// A bunch of string processing. The compute_checksum function builds a
// histogram and then sorts it by occurrence first and alphabet second, which
// gives us what we need.
//
// The deciphering function is simple as well. I ran it over the data once to
// see what string we were looking for and then added a check for that in the
// loop.

struct room {
  string name, checksum;
  int id;
};

room parse(const string& input) {
  room r;

  auto cs = input.find('[');
  auto ce = input.find(']');
  check(cs != string::npos && ce != string::npos, "parse checksum");
  r.checksum = input.substr(cs + 1, ce - cs - 1);

  auto secs = input.find_first_of("0123456789");
  check(secs != string::npos, "parse secid");
  r.id = stoi(input.substr(secs, cs-secs));
  r.name = input.substr(0, secs - 1);

  return r;
}

string compute_checksum(const string& name) {
  map<char, int> hist;
  for (char c : name) {
    if(c != '-') {
      hist[c]++;
    }
  }

  using p = pair<char, int>;
  vector<p> histv(hist.begin(), hist.end());
  check(histv.size() >= 5, "histv size");

  sort(histv.begin(), histv.end(), [](p l, p r) {
    if (l.second != r.second) {
      return l.second > r.second;
    }
    return l.first < r.first;
  });
  string checksum;
  for (int i= 0; i != 5; ++i) {
    checksum += histv[i].first;
  }
  return checksum;
}

char rotate_char(char c, int r) {
  return 'a' + (((c - 'a') + r) % 26);
}

char rotate_dash(char c, int r) {
  if (r & 1) {
    return c == '-' ? ' ' : '-';
  }
  return c;
}

string decipher(const room& r) {
  string deciphered;
  for (char c : r.name) {
    if (c == '-') {
      deciphered += rotate_dash(c, r.id);
    } else {
      deciphered += rotate_char(c, r.id);
    }
  }
  return deciphered;
}

int main() {
  int sum = 0;
  for (string line : get_file_lines("aoc-4.txt")) {
    room r = parse(line);
    if (compute_checksum(r.name) == r.checksum) {
      sum += r.id;
      if (decipher(r).find("northpole") != string::npos) {
        cout << decipher(r) << ": " << r.id << "\n";
      }
    }
  }
  cout << sum << "\n";
}
