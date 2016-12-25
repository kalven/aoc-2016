#include "aoc.h"

// Yet another brute force solution. Runtime for both parts combined was 0.25s.

string round(const string& input) {
  string res = input + '0';
  res.append(input.rbegin(), input.rend());
  for (size_t i = res.size() - input.size(); i != res.size(); ++i) {
    res[i] = res[i] == '0' ? '1' : '0';
  }
  return res;
}

string generate_data(const string& input, size_t length) {
  string res = input;
  while (res.size() < length) {
    res = round(res);
  }
  return res.substr(0, length);
}

string checksum(const string& input) {
  string check = input;
  while ((check.size() % 2) == 0) {
    string check2;
    for (int i = 0; i != check.size(); i += 2) {
      check2.push_back((check[i] == check[i + 1]) ? '1' : '0');
    }
    check.swap(check2);
  }
  return check;
}

int main() {
  string input = "11101000110010100";

  cout << checksum(generate_data(input, 272)) << "\n";
  cout << checksum(generate_data(input, 35651584)) << "\n";
}
