cmake_minimum_required(VERSION 3.12)
project(DAC_Code_Challenge)

set(CMAKE_CXX_STANDARD 14)

# GoogleTest
include(ExternalProject)
ExternalProject_Add(gtest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)
message(STATUS "GTest source dir = ${source_dir}")
message(STATUS "GTest binary dir = ${binary_dir}")


set(SOURCES 
        main.cpp 
        job.cpp
        jobsolver.cpp
        group.cpp
        parser.cpp
)

add_executable(solve_dependencies ${SOURCES})

add_dependencies(solve_dependencies gtest)
include_directories(${source_dir}/googletest/include)
target_link_libraries(solve_dependencies ${binary_dir}/lib/libgtest.a)
target_link_libraries(solve_dependencies ${binary_dir}/lib/libgtest_main.a)
target_compile_features(solve_dependencies PUBLIC cxx_std_20)

enable_testing()
add_test(NAME           solve_dependencies
         COMMAND        solve_dependencies)
