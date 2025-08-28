#include "fibonacci_matrix.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int n = (argc == 2) ? std::atoi(argv[1]) : 10;
    std::cout << fibonacci_matrix(n) << std::endl;
    return 0;
}
