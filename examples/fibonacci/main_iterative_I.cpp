#include "fibonacci_iterative_I.hpp"
#include <cstdlib>
#include <iostream>

int
main (int argc, char *argv[])
{
  uint8_t n = (argc == 2) ? std::atoi (argv[1]) : 10;
  std::cout << fibonacci_iterative_I (n) << std::endl;
  return 0;
}
