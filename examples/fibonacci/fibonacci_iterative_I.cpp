#include "fibonacci_iterative_I.hpp"

uint64_t
fibonacci_iterative_I (uint8_t n)
{
  if (n <= 1)
  {
    return n;
  }
  uint64_t prev = 0;
  uint64_t curr = 1;
  for (uint8_t i = 2; i <= n; ++i)
  {
    auto const next = prev + curr;
    prev = curr;
    curr = next;
  }
  return curr;
}
