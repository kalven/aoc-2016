#include "aoc.h"

// Again a fairly straightforward implementation. Since cpy and jnz had two
// different modes (register and immediate), I implemented those as different
// instructions. This turned out to be a bit of a bummer for day 23. Oh
// well. Runtime for both parts was about 10ms.

struct op {
  enum { cpy_reg, cpy_imm, jnz_reg, jnz_imm, inc, dec };
  int src;
  int dst;
  int type;
};

int main() {
  vector<string> input = {
      "cpy 1 a",  "cpy 1 b", "cpy 26 d", "jnz c 2",  "jnz 1 5",  "cpy 7 c",
      "inc d",    "dec c",   "jnz c -2", "cpy a c",  "inc a",    "dec b",
      "jnz b -2", "cpy c b", "dec d",    "jnz d -6", "cpy 14 c", "cpy 14 d",
      "inc a",    "dec d",   "jnz d -2", "dec c",    "jnz c -5",
  };

  vector<op> ops;
  for (const string& inst : input) {
    op o;
    char src_reg, dst_reg;
    if (sscanf(inst.c_str(), "cpy %d %c", &o.src, &dst_reg) == 2) {
      o.dst = dst_reg - 'a';
      o.type = op::cpy_imm;
    } else if (sscanf(inst.c_str(), "cpy %c %c", &src_reg, &dst_reg) == 2) {
      o.src = src_reg - 'a';
      o.dst = dst_reg - 'a';
      o.type = op::cpy_reg;
    } else if (sscanf(inst.c_str(), "jnz %d %d", &o.src, &o.dst) == 2) {
      o.type = op::jnz_imm;
    } else if (sscanf(inst.c_str(), "jnz %c %d", &src_reg, &o.dst) == 2) {
      o.src = src_reg - 'a';
      o.type = op::jnz_reg;
    } else if (sscanf(inst.c_str(), "inc %c", &dst_reg) == 1) {
      o.dst = dst_reg - 'a';
      o.type = op::inc;
    } else if (sscanf(inst.c_str(), "dec %c", &dst_reg) == 1) {
      o.dst = dst_reg - 'a';
      o.type = op::dec;
    } else {
      check(false, "parse err: " + inst);
    }
    ops.push_back(o);
  }

  int regs[4] = {0, 0, 0, 0}; // For part one.
  // int regs[4] = {0, 0, 1, 0}; // For part two.
  int pc = 0;

  while (pc >= 0 && pc < ops.size()) {
    op& o = ops[pc];
    switch (o.type) {
      case op::cpy_imm:
        regs[o.dst] = o.src;
        pc++;
        break;
      case op::cpy_reg:
        regs[o.dst] = regs[o.src];
        pc++;
        break;
      case op::jnz_imm:
        if (o.src) {
          pc += o.dst;
        } else {
          pc++;
        }
        break;
      case op::jnz_reg:
        if (regs[o.src]) {
          pc += o.dst;
        } else {
          pc++;
        }
        break;
      case op::inc:
        regs[o.dst]++;
        pc++;
        break;
      case op::dec:
        regs[o.dst]--;
        pc++;
        break;
    }
  }

  cout << "State\n"
       << "a: " << regs[0] << "\n"
       << "b: " << regs[1] << "\n"
       << "c: " << regs[2] << "\n"
       << "d: " << regs[3] << "\n";
}
