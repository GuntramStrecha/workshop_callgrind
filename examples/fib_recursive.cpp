#include <iostream>

constexpr int fib(int const n) { return (n > 1) ? fib(n - 1) + fib(n - 2) : n; }

int main(int argc, char**)
{
  auto const result = fib(argc == 1 ? 35 : 0);
  return result == 9227465 ? 0 : 1;
}
