#include "fibonacci_binet.hpp"
#include "fibonacci_dp.hpp"
#include "fibonacci_fast_doubling.hpp"
#include "fibonacci_generator.hpp"
#include "fibonacci_iterative_I.hpp"
#include "fibonacci_iterative_II.hpp"
#include "fibonacci_matrix.hpp"
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>

int
main (int, char *[])
{
  std::random_device rd;
  std::mt19937 gen (rd ());
  std::uniform_int_distribution<uint8_t> dis (0, 70);

  constexpr uint32_t LOOPS = 10000;

  for (uint32_t i = 0; i < LOOPS; ++i)
  {
    uint8_t const n = dis (gen);

    auto const results = { fibonacci_dp (n),          fibonacci_fast_doubling (n), fibonacci_generator (n),
                           fibonacci_iterative_I (n), fibonacci_iterative_II (n),  fibonacci_matrix (n) };
    auto const fib_binet = fibonacci_binet (n);

    auto const is_not_equal_to_binet = [fib_binet] (auto const &val) { return val != fib_binet; };

    if (std::any_of (results.begin (), results.end (), is_not_equal_to_binet))
    {
      if (std::all_of (results.begin (), results.end (), is_not_equal_to_binet))
      {
        std::cout << "Calculation using Binet's formula gives a different result for n = " << static_cast<uint32_t> (n)
                  << ":\n"
                  << "  Binet: " << fib_binet << '\n'
                  << "  Others:" << *results.begin () << '\n';
      }
      else
      {
        std::cerr << "Different results for other implementations for n = " << static_cast<uint32_t> (n) << ":\n"
                  << "  Binet: " << fib_binet << '\n'
                  << "  Others:";
        std::copy (results.begin (), results.end (), std::ostream_iterator<uint64_t> (std::cerr, " "));
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
