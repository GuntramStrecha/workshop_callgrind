#include "fibonacci_optimized.hpp"
#include <utility>

int64_t fibonacci_optimized(int n)
{
  if (n <= 1) return n;
  int64_t prev = 0, curr = 1;
  for (int i = 2; i <= n; ++i) { prev = std::exchange(curr, prev + curr); }
  return curr;
}
