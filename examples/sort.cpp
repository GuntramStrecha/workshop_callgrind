#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    const int N = 10000;
    std::vector<int> data(N);
    std::mt19937 rng(42);
    std::generate(data.begin(), data.end(), rng);

    std::sort(data.begin(), data.end());

    std::cout << "First element: " << data[0] << ", Last element: " << data[N-1] << std::endl;
    return 0;
}
