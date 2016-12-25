#include "aoc.h"

// I used a struct to represent a bot and a map to contain all bots. When bot is
// ready to "act", it is put on a queue. This queue is processed until it is
// done. The solution for part 1 is output as it is performed.

struct bot {
  int id = -1;
  int lo = -1, hi = -1;
  int lo_bot_out = -1, hi_bot_out = -1;
  int lo_out = -1, hi_out = -1;

  void give(int value) {
    check(value != -1, "value err");
    if (lo == -1) {
      lo = value;
    } else {
      hi = value;
    }
    int x = min(lo, hi);
    int y = max(lo, hi);
    lo = x;
    hi = y;

    if (lo == 17 && hi == 61) {
      cout << "bot " << id << "\n";
    }
  }

  bool complete() {
    if (lo == -1 || hi == -1) {
      return false;
    }
    int outs = ((lo_bot_out != -1) + (hi_bot_out != -1) + (lo_out != -1) +
                (hi_out != -1));
    check(outs <= 2, "out err");
    return outs == 2;
  }
};

int main() {
  vector<string> input = get_file_lines("aoc-10.txt");

  map<int, bot> bots;
  map<int, int> outputs;
  queue<int> act;

  auto queue_if_complete = [&](int bot_no) {
    if (bots[bot_no].complete()) {
      act.push(bot_no);
    }
  };

  for (const string& line : input) {
    int bot_no, value;
    char lo_type[16], hi_type[16];
    int lo_dest, hi_dest;

    if (sscanf(line.c_str(), "value %d goes to bot %d", &value, &bot_no) == 2) {
      bot& b = bots[bot_no];
      b.id = bot_no;
      b.give(value);
      queue_if_complete(bot_no);
    } else if (sscanf(line.c_str(),
                      "bot %d gives low to %s %d and high to %s %d", &bot_no,
                      lo_type, &lo_dest, hi_type, &hi_dest)) {
      bot& b = bots[bot_no];
      b.id = bot_no;
      check(lo_type[0] == 'b' || lo_type[0] == 'o', "lo err");
      if (lo_type[0] == 'b') {
        b.lo_bot_out = lo_dest;
      } else {
        b.lo_out = lo_dest;
      }
      check(hi_type[0] == 'b' || hi_type[0] == 'o', "hi err");
      if (hi_type[0] == 'b') {
        b.hi_bot_out = hi_dest;
      } else {
        b.hi_out = hi_dest;
      }
      queue_if_complete(bot_no);
    }
  }

  while (!act.empty()) {
    int bot_no = act.front();
    act.pop();
    bot& b = bots[bot_no];
    check(b.complete(), "complete err");

    if (b.lo_bot_out != -1) {
      bots[b.lo_bot_out].id = b.lo_bot_out;
      bots[b.lo_bot_out].give(b.lo);
      b.lo = -1;
      queue_if_complete(b.lo_bot_out);
    }
    if (b.hi_bot_out != -1) {
      bots[b.hi_bot_out].id = b.hi_bot_out;
      bots[b.hi_bot_out].give(b.hi);
      b.hi = -1;
      queue_if_complete(b.hi_bot_out);
    }
    if (b.lo_out != -1) {
      outputs[b.lo_out] = b.lo;
      b.lo = -1;
    }
    if (b.hi_out != -1) {
      outputs[b.hi_out] = b.hi;
      b.hi = -1;
    }
  }

  cout << outputs[0] * outputs[1] * outputs[2] << "\n";
}
