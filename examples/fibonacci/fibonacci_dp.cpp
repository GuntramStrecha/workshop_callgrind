#include "fibonacci_dp.hpp"
#include <vector>

uint64_t
fibonacci_dp (uint8_t n)
{
  if (n <= 1)
  {
    return n;
  }
  std::vector<uint64_t> dp (n + 1);
  dp[0] = 0;
  dp[1] = 1;
  for (uint8_t i = 2; i <= n; ++i)
  {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}
