#include "fibonacci_all.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <random>

int main (int, char *[])
{
  std::random_device rd;
  std::mt19937 gen (rd ());
  std::uniform_int_distribution<uint8_t> dis (1, 70);

  constexpr uint32_t LOOPS = 10000;

  for (uint32_t i = 0; i < LOOPS; ++i)
  {
    uint8_t const n = dis (gen);
    auto const fibonacci_algorithms = getFibonacciAlgorithms();
    std::vector<uint64_t> results;

    std::transform(fibonacci_algorithms.begin(), fibonacci_algorithms.end(), std::back_inserter(results), [n](auto const& alg) { return alg(n); });

    if (std::any_of (results.begin (), results.end (), [](auto const val){ return val == 0;}))
    {
        return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
