#include <cmath>

int fib(int n)
{
  if (n <= 1) return n;
  static const auto sqrt5 = std::sqrt(5);
  static const auto phi   = (1 + sqrt5) / 2;
  static const auto psi   = (1 - sqrt5) / 2;
  return static_cast<int>((std::pow(phi, n) - std::pow(psi, n)) / sqrt5 + 0.5);
}

int main(int argc, char**)
{
  auto const result = fib(argc == 1 ? 35 : 0);
  return result == 9227465 ? 0 : 1;
}
