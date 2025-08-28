#include "fibonacci_generator.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int n = (argc == 2) ? std::atoi(argv[1]) : 10;
    auto gen = fibonacci_generator();
    int64_t value = 0;
    for (int i = 0; i <= n; ++i) {
        value = gen.next().value();
    }
    std::cout << value << std::endl;
    return 0;
}
