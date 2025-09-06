cmake_minimum_required(VERSION 3.16)
project(FibonacciExamples LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the fibonacci subfolder
add_subdirectory(examples/fibonacci)