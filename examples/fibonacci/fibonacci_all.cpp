#include "fibonacci_all.hpp"
#include "fibonacci_binet.hpp"
#include "fibonacci_dp.hpp"
#include "fibonacci_fast_doubling.hpp"
#include "fibonacci_generator.hpp"
#include "fibonacci_iterative_I.hpp"
#include "fibonacci_iterative_II.hpp"
#include "fibonacci_matrix.hpp"

std::array<uint64_t (*)(uint8_t const), 7> getFibonacciAlgorithms()
{
	return { fibonacci_binet,
		     fibonacci_dp,
			 fibonacci_fast_doubling,
			 fibonacci_generator,
			 fibonacci_iterative_I,
			 fibonacci_iterative_II,
			 fibonacci_matrix
	};
}
