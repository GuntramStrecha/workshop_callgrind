#pragma once

#include<array>
#include <cstdint>

std::array<uint64_t (*)(uint8_t const), 7> getFibonacciAlgorithms();
