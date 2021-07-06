# submodules/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")

if(CYGWIN)
# fix broken googletest pthread detection on cygwin that causes sigabrt
# Condition has_owner_ && pthread_equal(owner_, pthread_self()) failed. The current thread is not holding the mutex @0x10045e030
  add_compile_definitions(GTEST_HAS_PTHREAD=1)
elseif(WIN32)
# override googletest windows runtime library setting that uses -MDd
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_subdirectory(fmt EXCLUDE_FROM_ALL)

