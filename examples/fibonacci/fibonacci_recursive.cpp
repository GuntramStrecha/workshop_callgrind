#include "fibonacci_recursive.hpp"

uint64_t
fibonacci_recursive (uint8_t n)
{
  if (n <= 1)
  {
    return n;
  }
  return fibonacci_recursive (n - 1) + fibonacci_recursive (n - 2);
}
