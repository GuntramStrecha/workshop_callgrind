cmake_minimum_required(VERSION 3.16)
project(FibonacciExamples LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List of implementations
set(FIB_IMPLS
    fibonacci_recursive
    fibonacci_iterative
    fibonacci_dp
    fibonacci_optimized
    fibonacci_matrix
    fibonacci_binet
    fibonacci_fast_doubling
    fibonacci_generator
)

# Create a library for each implementation
foreach(IMPL ${FIB_IMPLS})
    add_library(${IMPL} STATIC examples/${IMPL}.cpp)
    target_include_directories(${IMPL} PUBLIC examples)
endforeach()

# Add executables for each Fibonacci example
add_executable(main_recursive examples/main_recursive.cpp)
target_link_libraries(main_recursive fibonacci_recursive)
add_executable(main_iterative examples/main_iterative.cpp)
target_link_libraries(main_iterative fibonacci_iterative)
add_executable(main_dp examples/main_dp.cpp)
target_link_libraries(main_dp fibonacci_dp)
add_executable(main_optimized examples/main_optimized.cpp)
target_link_libraries(main_optimized fibonacci_optimized)
add_executable(main_matrix examples/main_matrix.cpp)
target_link_libraries(main_matrix fibonacci_matrix)
add_executable(main_binet examples/main_binet.cpp)
target_link_libraries(main_binet fibonacci_binet)
add_executable(main_fast_doubling examples/main_fast_doubling.cpp)
target_link_libraries(main_fast_doubling fibonacci_fast_doubling)
add_executable(main_generator examples/main_generator.cpp)
target_link_libraries(main_generator fibonacci_generator)