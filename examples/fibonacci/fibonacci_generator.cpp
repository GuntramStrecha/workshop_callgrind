#include "fibonacci_generator.hpp"
#include <cstdint>
#include <generator>

std::generator<uint64_t>
fibonacci_generator ()
{
  uint64_t prev = 0;
  uint64_t curr = 1;
  co_yield prev;
  co_yield curr;
  while (true)
  {
    auto const next = prev + curr;
    co_yield next;
    prev = curr;
    curr = next;
  }
}

uint64_t
fibonacci_generator (uint8_t n)
{
  auto gen = fibonacci_generator ();
  auto it = gen.begin ();
  uint64_t value = 0;
  for (uint8_t i = 0; i <= n && it != gen.end (); ++i, ++it)
  {
    value = *it;
  }
  return value;
}
