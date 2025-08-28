#include "fibonacci_matrix.hpp"
#include <array>

static std::array<std::array<int64_t, 2>, 2> multiply(const std::array<std::array<int64_t, 2>, 2>& a, const std::array<std::array<int64_t, 2>, 2>& b) {
    return {{
        {a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]},
        {a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]}
    }};
}

static std::array<std::array<int64_t, 2>, 2> matrix_pow(std::array<std::array<int64_t, 2>, 2> m, int n) {
    std::array<std::array<int64_t, 2>, 2> result = {{{1, 0}, {0, 1}}};
    while (n > 0) {
        if (n % 2 == 1) result = multiply(result, m);
        m = multiply(m, m);
        n /= 2;
    }
    return result;
}

int64_t fibonacci_matrix(int n) {
    if (n <= 1) return n;
    std::array<std::array<int64_t, 2>, 2> base = {{{1, 1}, {1, 0}}};
    auto res = matrix_pow(base, n - 1);
    return res[0][0];
}