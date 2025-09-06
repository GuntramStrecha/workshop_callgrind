#include "fibonacci_binet.hpp"
#include <cmath>

uint64_t
fibonacci_binet (uint8_t n)
{
  static const double sqrt5 = std::sqrt (5.0);
  static const double phi = (1.0 + sqrt5) / 2.0;
  return static_cast<uint64_t> (std::round (std::pow (phi, n) / sqrt5));
}
