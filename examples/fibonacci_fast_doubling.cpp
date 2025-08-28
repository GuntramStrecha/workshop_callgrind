#include "fibonacci_fast_doubling.hpp"
#include <utility>

static std::pair<int64_t, int64_t> fib_pair(int n)
{
  if (n == 0) return {0, 1};
  auto    p = fib_pair(n >> 1);
  int64_t c = p.first * (2 * p.second - p.first);
  int64_t d = p.first * p.first + p.second * p.second;
  if (n & 1)
    return {d, c + d};
  else
    return {c, d};
}

int64_t fibonacci_fast_doubling(int n) { return fib_pair(n).first; }
