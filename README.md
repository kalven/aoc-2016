## Advent of Code 2016 solutions

These are my solutions for Advent of Code 2016. All should compile with a recent
GCC without any particular flags (though, -O3 will be nice for some
problems). Solutions for day 19 & 20 use boost, all other days get by with the
standard library only.

I was going for leaderboard placement on most days. This means the code was
written with these priorities:

 * Fast development.

 * If the problem called for it, fast runtime.

 * ...

 * ... elegance?

Some programs output solutions for both parts. Some programs require a tweak to
a single line to produce the solution for part two. If the difference is more
than one or two lines, the two solutions are split up into separate .cpp
files. Some programs load input from file, some have the input hardcoded into
the source.
