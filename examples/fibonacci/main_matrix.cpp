#include "fibonacci_matrix.hpp"
#include <cstdlib>
#include <iostream>

int
main (int argc, char *argv[])
{
  uint8_t n = (argc == 2) ? std::atoi (argv[1]) : 10;
  std::cout << fibonacci_matrix (n) << std::endl;
  return 0;
}
