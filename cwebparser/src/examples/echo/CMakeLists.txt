# examples/echo/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)

project(echo_cweb)

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -O0 -ggdb3)
elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
# ranges library cannot take -Wall -WX
target_compile_options(${PROJECT_NAME} PRIVATE -Od)
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _SILENCE_CLANG_CONCEPTS_MESSAGE)
endif()

target_link_libraries(${PROJECT_NAME} cwebparse cwebbisonparser.v4.flex cwebbisonparser.v4.bison)


