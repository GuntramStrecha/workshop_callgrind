#include "fibonacci_optimized.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int n = (argc == 2) ? std::atoi(argv[1]) : 10;
    std::cout << fibonacci_optimized(n) << std::endl;
    return 0;
}
