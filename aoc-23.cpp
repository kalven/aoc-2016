#include "aoc.h"

// I initially tried to reuse the assembunny implementation from day 12. The
// representation I used there made tgl (toggle) harder to implement, so I
// scrapped it.
//
// The program that is executed essentially ends up doing a bunch of
// multiplications (in the form of nested loops). The problem text for part 2
// hinted about this. To get it running in a reasonable amount of time, I added
// a simple peephole optimization that detected the multiplication
// pattern. Runtime for both parts is 2ms with this optimization.

struct op {
  enum { cpy, jnz, inc, dec, tgl };
  int type;
  char arg0[16] = {};
  char arg1[16] = {};
};

int main() {
  vector<string> input = {
      "cpy a b", "dec b",    "cpy a d",  "cpy 0 a",  "cpy b c", "inc a",
      "dec c",   "jnz c -2", "dec d",    "jnz d -5", "dec b",   "cpy b c",
      "cpy c d", "dec d",    "inc c",    "jnz d -2", "tgl c",   "cpy -16 c",
      "jnz 1 c", "cpy 90 c", "jnz 73 d", "inc a",    "inc d",   "jnz d -2",
      "inc c",   "jnz c -5",
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
    } else {
      check(false, "parse err: " + inst);
    }
    ops.push_back(o);
  }

  int regs[4] = {7, 0, 0, 0};
  // int regs[4] = {12, 0, 0, 0}; // Part two.
  int pc = 0;

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

  auto toggle = [](int type) -> int {
    switch (type) {
      case op::inc:
        return op::dec;
      case op::tgl:
      case op::dec:
        return op::inc;
      case op::jnz:
        return op::cpy;
      case op::cpy:
        return op::jnz;
      default:
        check(false, "unknown toggle");
        return 0;
    }
  };

  while (pc >= 0 && pc < ops.size()) {
    op& o = ops[pc];
    switch (o.type) {
      case op::cpy: {
        // Multiplication detection
        if (pc + 5 < ops.size() && ops[pc + 1].type == op::inc &&
            ops[pc + 2].type == op::dec && ops[pc + 3].type == op::jnz &&
            ops[pc + 4].type == op::dec && ops[pc + 5].type == op::jnz &&
            load_src(ops[pc + 3].arg1) == -2 &&
            load_src(ops[pc + 5].arg1) == -5) {

          auto& inc = ops[pc + 1];
          auto& dec1 = ops[pc + 2];
          auto& dec2 = ops[pc + 4];

          regs[reg_idx(inc.arg0)] +=
              (load_src(o.arg0) * regs[reg_idx(dec2.arg0)]);

          regs[reg_idx(dec1.arg0)] = 0;
          regs[reg_idx(dec2.arg0)] = 0;
          pc += 6;
        } else {
          if (is_reg(o.arg1)) {
            regs[reg_idx(o.arg1)] = load_src(o.arg0);
          }
          pc++;
        }
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
      case op::tgl: {
        int offset = load_src(o.arg0);
        if (pc + offset < ops.size()) {
          op& t = ops[pc + offset];
          t.type = toggle(t.type);
        }
        pc++;
        break;
      }
    }
  }

  cout << "State\n"
       << "a: " << regs[0] << "\n"
       << "b: " << regs[1] << "\n"
       << "c: " << regs[2] << "\n"
       << "d: " << regs[3] << "\n";
}
