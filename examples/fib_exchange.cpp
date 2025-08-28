#include <utility>

int fib(int n)
{
  int a = 0;
  int b = 1;

  while (a < n) { a = std::exchange(b, a); }

  return a;
}

int main(int argc, char**)
{
  auto const result = fib(argc == 1 ? 35 : 0);
  return result == 9227465 ? 0 : 1;
}
