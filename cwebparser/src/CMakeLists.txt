# cwebparser/src/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)

project(cwebparser_src_dir)

set(GRAMMAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/grammar)

add_subdirectory(bisonparser/${ParserVersion})
add_subdirectory(flexlexer/${ParserVersion})
add_subdirectory(parserapi/${ParserVersion})
add_subdirectory(examples)
