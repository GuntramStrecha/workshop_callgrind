# CMakeLists.txt for Fibonacci implementations

# Add all libraries and executables for Fibonacci implementations
set(FIB_IMPLS
    fibonacci_all
    fibonacci_binet
    fibonacci_dp
    fibonacci_fast_doubling
    fibonacci_generator
    fibonacci_iterative_I
    fibonacci_iterative_II
    fibonacci_matrix
    fibonacci_recursive
)

foreach(IMPL ${FIB_IMPLS})
    add_library(${IMPL} STATIC ${IMPL}.cpp)
    target_include_directories(${IMPL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

add_executable(main_recursive main_recursive.cpp)
target_link_libraries(main_recursive fibonacci_recursive)
add_executable(main_iterative_I main_iterative_I.cpp)
target_link_libraries(main_iterative_I fibonacci_iterative_I)
add_executable(main_dp main_dp.cpp)
target_link_libraries(main_dp fibonacci_dp)
add_executable(main_iterative_II main_iterative_II.cpp)
target_link_libraries(main_iterative_II fibonacci_iterative_II)
add_executable(main_matrix main_matrix.cpp)
target_link_libraries(main_matrix fibonacci_matrix)
add_executable(main_binet main_binet.cpp)
target_link_libraries(main_binet fibonacci_binet)
add_executable(main_fast_doubling main_fast_doubling.cpp)
target_link_libraries(main_fast_doubling fibonacci_fast_doubling)
add_executable(main_generator main_generator.cpp)
target_link_libraries(main_generator fibonacci_generator)
add_executable(main_all main_all.cpp)
target_link_libraries(main_all
    fibonacci_all
    fibonacci_binet
    fibonacci_dp
    fibonacci_fast_doubling
    fibonacci_generator
    fibonacci_iterative_I
    fibonacci_iterative_II
    fibonacci_matrix
    fibonacci_recursive
)

add_executable(main_matrix_gprof main_matrix.cpp fibonacci_matrix.cpp)
target_compile_options(main_matrix_gprof PRIVATE -pg)
target_link_options(main_matrix_gprof PRIVATE -pg)
