#include "aoc.h"

// Yet another assembunny program. This time I was able to reuse the
// implementation from day 23. I added support for the "out" instruction. This
// instruction would check if the required pattern was produced or not. If the
// pattern was broken, it would skip ahead to the next input state and try
// again. If the pattern was kept up for 100 (arbitrarily chosen) iterations,
// then the search would be done. Runtime about 0.25s.

struct op {
  enum { cpy, jnz, inc, dec, tgl, out };
  int type;
  char arg0[16] = {};
  char arg1[16] = {};
};

int main() {
  vector<string> input = {
      "cpy a d", "cpy 7 c",  "cpy 362 b", "inc d",   "dec b",     "jnz b -2",
      "dec c",   "jnz c -5", "cpy d a",   "jnz 0 0", "cpy a b",   "cpy 0 a",
      "cpy 2 c", "jnz b 2",  "jnz 1 6",   "dec b",   "dec c",     "jnz c -4",
      "inc a",   "jnz 1 -7", "cpy 2 b",   "jnz c 2", "jnz 1 4",   "dec b",
      "dec c",   "jnz 1 -4", "jnz 0 0",   "out b",   "jnz a -19", "jnz 1 -21",
  };

  vector<op> ops;
  for (const string& inst : input) {
    op o;
    memset(o.arg0, 0, sizeof(o.arg0));
    memset(o.arg1, 0, sizeof(o.arg1));
    if (sscanf(inst.c_str(), "cpy %s %s", &o.arg0, &o.arg1) == 2) {
      o.type = op::cpy;
    } else if (sscanf(inst.c_str(), "jnz %s %s", &o.arg0, &o.arg1) == 2) {
      o.type = op::jnz;
    } else if (sscanf(inst.c_str(), "inc %s", &o.arg0) == 1) {
      o.type = op::inc;
    } else if (sscanf(inst.c_str(), "dec %s", &o.arg0) == 1) {
      o.type = op::dec;
    } else if (sscanf(inst.c_str(), "tgl %s", &o.arg0) == 1) {
      o.type = op::tgl;
    } else if (sscanf(inst.c_str(), "out %s", &o.arg0) == 1) {
      o.type = op::out;
    } else {
      check(false, "parse err: " + inst);
    }
    ops.push_back(o);
  }

  for (int test = 0;; ++test) {
    int regs[4] = {test, 0, 0, 0};
    int pc = 0;

    const int out_dummy = -999999;
    int last_out = out_dummy;
    int last_streak = 0;

    auto is_reg = [&](const char* arg) {
      return (arg[1] == '\0' && arg[0] >= 'a' && arg[0] <= 'd');
    };

    auto reg_idx = [&](const char* arg) {
      check(is_reg(arg), "reg_idx on non-reg");
      return arg[0] - 'a';
    };

    auto load_src = [&](const char* arg) {
      if (is_reg(arg)) {
        return regs[reg_idx(arg)];
      }
      return atoi(arg);
    };

    while (pc >= 0 && pc < ops.size()) {
      op& o = ops[pc];
      switch (o.type) {
        case op::cpy: {
          if (is_reg(o.arg1)) {
            regs[reg_idx(o.arg1)] = load_src(o.arg0);
          }
          pc++;
          break;
        }
        case op::jnz:
          if (load_src(o.arg0)) {
            pc += load_src(o.arg1);
          } else {
            pc++;
          }
          break;
        case op::inc:
          regs[reg_idx(o.arg0)]++;
          pc++;
          break;
        case op::dec:
          regs[reg_idx(o.arg0)]--;
          pc++;
          break;
        case op::out: {
          int v = load_src(o.arg0);

          if (last_out == out_dummy) {
            last_out = v;
          } else {
            if (v != !(last_out)) {
              pc = ops.size();
              continue;
            }
            last_out = v;
          }

          if (++last_streak == 100) {
            cout << "found at " << test << "\n";
            return 0;
          }
          pc++;
          break;
        }
      }
    }
  }
}
