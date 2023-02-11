cmake_minimum_required(VERSION 3.12)
project(DAC_Code_Challenge)

set(CMAKE_CXX_STANDARD 20)

# Manually change to build tests because CMake is being weird :))
set(DEBUG TRUE)

if(${DEBUG})
        set(_TEST TRUE)
        add_compile_definitions(_TEST=1)
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

endif()

set(SOURCES 
        source/main.cpp 
        source/job/job.cpp
        source/jobsolver/jobsolver.cpp
        source/group/group.cpp
        source/parser/parser.cpp
)

if(${_TEST}) 
        set(SOURCES
                ${SOURCES}
                source/tests/tests.cpp
        )
endif()

add_executable(solve_dependencies ${SOURCES})
target_compile_features(solve_dependencies PUBLIC cxx_std_20)

if(${_TEST})
        add_dependencies(solve_dependencies gtest)
        include_directories(${source_dir}/googletest/include)
        target_link_libraries(solve_dependencies ${binary_dir}/lib/libgtest.a)
        target_link_libraries(solve_dependencies ${binary_dir}/lib/libgtest_main.a)

        enable_testing()
        add_test(NAME           solve_dependencies
                 COMMAND        solve_dependencies)
 endif()
