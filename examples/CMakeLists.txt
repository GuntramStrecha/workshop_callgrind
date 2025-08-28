cmake_minimum_required(VERSION 3.10)
project(CallgrindExamples CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")

add_executable(fib_recursive fib_recursive.cpp)
add_executable(fib_iterative fib_iterative.cpp)
add_executable(fib_binet fib_binet.cpp)
add_executable(fib_exchange fib_exchange.cpp)
add_executable(sort sort.cpp)
add_executable(matrix_mult matrix_mult.cpp)
