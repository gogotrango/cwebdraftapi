# cwebparser/src/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)

get_filename_component(COMPNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${COMPNAME})

set(GRAMMAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/grammar)

add_subdirectory(bisonparser/${ParserVersion})
add_subdirectory(flexlexer/${ParserVersion})
add_subdirectory(parserapi/${ParserVersion})
add_subdirectory(examples/echo)
