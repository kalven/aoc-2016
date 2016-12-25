// Header used in all solutions.

#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <regex>
#include <tuple>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

using namespace std;

inline string get_file_contents(const string& filename) {
  ifstream in(filename);
  if (!in.is_open()) {
    throw runtime_error("Cannot open " + filename);
  }
  stringstream ss;
  ss << in.rdbuf();
  string content = ss.str();
  if (content.empty()) {
    throw runtime_error("Empty contents " + filename);
  }
  return content;
}

inline vector<string> get_file_lines(const string& filename) {
  ifstream in(filename);
  if (!in.is_open()) {
    throw runtime_error("Cannot open " + filename);
  }
  string line;
  vector<string> lines;
  while (getline(in, line)) {
    lines.push_back(line);
  }
  return lines;
}

inline vector<string> split(const string& input, char delim) {
  istringstream is(input);

  string chunk;
  vector<string> chunks;
  while (getline(is, chunk, delim)) {
    chunks.push_back(chunk);
  }
  return chunks;
}

inline string trim(const string& input) {
  const char ws[] = " \r\n\t";
  auto s = input.find_first_not_of(ws);
  if (s == string::npos) {
    return "";
  }
  auto e = input.find_last_not_of(ws);
  return input.substr(s, e - s + 1);
}

void check(bool c, const string& err) {
  if (!c) {
    throw runtime_error(err);
  }
}

