#include "fibonacci_matrix.hpp"
#include <array>

using matrix_2x2 = std::array<std::array<uint64_t, 2>, 2>;

static matrix_2x2
multiply (matrix_2x2 const &a, matrix_2x2 const &b)
{
  return { { { a[0][0] * b[0][0] + a[0][1] * b[1][0],
               a[0][0] * b[0][1] + a[0][1] * b[1][1] },
             { a[1][0] * b[0][0] + a[1][1] * b[1][0],
               a[1][0] * b[0][1] + a[1][1] * b[1][1] } } };
}

static matrix_2x2
matrix_pow (matrix_2x2 m, uint8_t n)
{
  matrix_2x2 result = { { { 1, 0 }, { 0, 1 } } };
  while (n > 0)
  {
    if (n & 1)
    {
      result = multiply (result, m);
    }
    m = multiply (m, m);
    n >>= 1;
  }
  return result;
}

uint64_t
fibonacci_matrix (uint8_t n)
{
  if (n <= 1)
  {
    return n;
  }
  matrix_2x2 base = { { { 1, 1 }, { 1, 0 } } };
  auto res = matrix_pow (base, n - 1);
  return res[0][0];
}
