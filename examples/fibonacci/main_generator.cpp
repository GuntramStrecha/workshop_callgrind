#include "fibonacci_generator.hpp"
#include <cstdlib>
#include <iostream>

int
main (int argc, char *argv[])
{
  uint8_t n = (argc == 2) ? std::atoi (argv[1]) : 10;
  std::cout << fibonacci_generator (n) << std::endl;
  return 0;
}
