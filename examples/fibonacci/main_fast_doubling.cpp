#include "fibonacci_fast_doubling.hpp"
#include <cstdlib>
#include <iostream>

int
main (int argc, char *argv[])
{
  uint8_t n = (argc == 2) ? std::atoi (argv[1]) : 10;
  std::cout << fibonacci_fast_doubling (n) << std::endl;
  return 0;
}
