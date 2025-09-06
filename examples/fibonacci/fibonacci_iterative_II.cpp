#include "fibonacci_iterative_II.hpp"
#include <utility>

uint64_t
fibonacci_iterative_II (uint8_t n)
{
  if (n <= 1)
  {
    return n;
  }
  uint64_t prev = 0;
  uint64_t curr = 1;
  for (uint8_t i = 2; i <= n; ++i)
  {
    prev = std::exchange (curr, prev + curr);
  }
  return curr;
}
