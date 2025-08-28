#include "fibonacci_binet.hpp"
#include <cmath>

int64_t fibonacci_binet(int n) {
    static const double sqrt5 = std::sqrt(5.0);
    static const double phi = (1.0 + sqrt5) / 2.0;
    return static_cast<int64_t>(std::round(std::pow(phi, n) / sqrt5));
}