# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/src/gtest"
  "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/src/gtest-build"
  "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest"
  "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/tmp"
  "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/src/gtest-stamp"
  "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/src"
  "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/src/gtest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/src/gtest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mathias/Documents/C++/DAC_Code_Challenge/build/test/gtest/src/gtest-stamp${cfgdir}") # cfgdir has leading slash
endif()
