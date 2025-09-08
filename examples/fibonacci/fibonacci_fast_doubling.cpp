#include "fibonacci_fast_doubling.hpp"
#include <utility>

static std::pair<uint64_t, uint64_t>
fib_pair (uint8_t n)
{
  if (n == 0)
  {
    return { 0, 1 };
  }
  auto p = fib_pair (n >> 1);
  uint64_t c = p.first * (2 * p.second - p.first);
  uint64_t d = p.first * p.first + p.second * p.second;
  if (n & 1)
  {
    return { d, c + d };
  }
  else
  {
    return { c, d };
  }
}

uint64_t
fibonacci_fast_doubling (uint8_t n)
{
  return fib_pair (n).first;
}
