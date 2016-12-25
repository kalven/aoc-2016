#include "aoc.h"

// Trivial modification of part one. Runtime for this part was about 12s.

enum Element { Polonium, Thulium, Promethium, Ruthenium, Cobalt, Elerium, Dilithium };

const int Elements = 7;
const int Objects = Elements * 2;

struct state {
  unsigned char objects[Objects];
  unsigned char elevator;

  unsigned char& generator(int floor) {
    return objects[floor * 2];
  }
  unsigned char& chip(int floor) {
    return objects[floor * 2 + 1];
  }
  unsigned char generator(int floor) const {
    return objects[floor * 2];
  }
  unsigned char chip(int floor) const {
    return objects[floor * 2 + 1];
  }

  char type(int object) const {
    return (object & 1) ? 'M' : 'G';
  }

  uint64_t as_int() const {
    uint64_t res = elevator;
    for (int i = 0; i != Objects; ++i) {
      res <<= 4;
      res |= objects[i] & 15;
    }
    return res;
  }

  // Returns true if the current state is possible (floors < 4) and not a bad
  // end state.
  bool valid() const {
    if (elevator > 3) {
      return false;
    }
    for (int i = 0; i != Objects; ++i) {
      if (objects[i] > 3) {
        return false;
      }
    }
    return true;
  }

  // Returns true if a chip is being irradiated by a generator.
  bool bad_end_state() const {
    for (int i = 0; i != Elements; i++) {
      // Chip and generator on the same level.
      if (chip(i) == generator(i)) {
        continue;
      }
      // Chip and generator on different levels, check that there are no other
      // generators on the level.
      for (int j = 0; j != Elements; j++) {
        if (i != j && chip(i) == generator(j)) {
          return true;
        }
      }
    }
    return false;
  }

  // Returns true if all objects are at the top floor.
  bool good_end_state() const {
    if (elevator != 3) {
      return false;
    }
    for (int i = 0; i != Objects; ++i) {
      if (objects[i] != 3) {
        return false;
      }
    }
    return true;
  }

  vector<state> moves() const {
    vector<state> result;
    auto add_state = [&](state new_state) {
      if (new_state.valid() && !new_state.bad_end_state()) {
        result.push_back(new_state);
      }
    };

    // Collect a list of all objects on the same floor as the elevator.
    vector<int> objs;
    for (int i = 0; i != Objects; ++i) {
      if (objects[i] == elevator) {
        objs.push_back(i);
      }
    }

    // Generate all two object moves.
    for (int i = 0; i != objs.size(); ++i) {
      const int first = objs[i];

      state one_up = *this;
      one_up.objects[first]++;
      one_up.elevator++;
      add_state(one_up);

      state one_down = *this;
      one_down.objects[first]--;
      one_down.elevator--;
      add_state(one_down);

      for (int j = i+1; j < objs.size(); ++j) {
        const int second = objs[j];

        state two_up = *this;
        two_up.objects[first]++;
        two_up.objects[second]++;
        two_up.elevator++;
        add_state(two_up);
        
        state two_down = *this;
        two_down.objects[first]--;
        two_down.objects[second]--;
        two_down.elevator--;
        add_state(two_down);
      }
    }

    return result;
  }
};

using state_move = pair<state, int>;

int main() {
  state start;
  start.elevator = 0;
  start.generator(Polonium) = 0;
  start.generator(Thulium) = 0;
  start.generator(Promethium) = 0;
  start.generator(Ruthenium) = 0;
  start.generator(Cobalt) = 0;
  start.generator(Dilithium) = 0;
  start.generator(Elerium) = 0;
  start.chip(Cobalt) = 0;
  start.chip(Thulium) = 0;
  start.chip(Ruthenium) = 0;
  start.chip(Polonium) = 1;
  start.chip(Promethium) = 1;
  start.chip(Dilithium) = 0;
  start.chip(Elerium) = 0;

  unordered_set<uint64_t> visited = {start.as_int()};
  queue<state_move> q;
  q.push({start, 0});

  int max_move = 0;

  vector<vector<int>> v = {{}};

  while (!q.empty()) {
    // Check if we're done.
    state_move m = q.front(); q.pop();
    if (m.first.good_end_state()) {
      cout << "solved in " << m.second << " moves\n";
      break;
    }

    if (m.second > max_move) {
      max_move = m.second;
      cout << "Done " << max_move << " moves (q:" << q.size() << ")\n";
    }

    // Make new moves.
    for (state new_state : m.first.moves()) {
      if (visited.count(new_state.as_int())) {
        // Already seen this move, ignore.
        continue;
      }
      q.push({new_state, m.second+1});
      visited.insert(new_state.as_int());
    }
  }
}
