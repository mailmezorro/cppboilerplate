# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/dani/git/cppboilerplate/build/gtest/src/googletest"
  "/home/dani/git/cppboilerplate/build/gtest/src/googletest-build"
  "/home/dani/git/cppboilerplate/build/gtest"
  "/home/dani/git/cppboilerplate/build/gtest/tmp"
  "/home/dani/git/cppboilerplate/build/gtest/src/googletest-stamp"
  "/home/dani/git/cppboilerplate/build/gtest/src"
  "/home/dani/git/cppboilerplate/build/gtest/src/googletest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/dani/git/cppboilerplate/build/gtest/src/googletest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/dani/git/cppboilerplate/build/gtest/src/googletest-stamp${cfgdir}") # cfgdir has leading slash
endif()
