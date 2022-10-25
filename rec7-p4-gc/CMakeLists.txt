cmake_minimum_required(VERSION 3.22)
project(rec7_p4_gc)

set(CMAKE_CXX_STANDARD 17)

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "This is Release!")
else()
    message(STATUS "This is Debug!")
endif()

add_executable(fib fib.cpp)
add_executable(fib-mem-resource fib-mem-resource.cpp)
target_link_libraries(fib argparse)
target_link_libraries(fib-alloc argparse)
