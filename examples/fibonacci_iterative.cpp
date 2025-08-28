#include "fibonacci_iterative.hpp"

int64_t fibonacci_iterative(int n) {
    if (n <= 1) return n;
    int64_t a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int64_t c = a + b;
        a = b;
        b = c;
    }
    return b;
}