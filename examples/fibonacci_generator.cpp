#include "fibonacci_generator.hpp"
#include <cstdint>
#include <generator>

std::generator<int64_t> fibonacci_generator()
{
  int64_t a = 0, b = 1;
  co_yield a;
  co_yield b;
  while (true)
  {
    int64_t next = a + b;
    co_yield next;
    a = b;
    b = next;
  }
}
