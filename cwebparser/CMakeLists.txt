# cwebparser/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)

project(cwebparser)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3" CACHE STRING "" FORCE)
  set(CMAKE_CXX_STANDARD 23 CACHE STRING "" FORCE)
endif()

set(ParserVersion v4)

if(NOT DEFINED CACHE{BISON})
  message(FATAL_ERROR "Please set BISON variable on cmake commandline to the path to bison 3.7 or higher")
endif()

add_subdirectory(../submodules submodules)

add_subdirectory(src)


