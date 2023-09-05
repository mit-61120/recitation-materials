cmake_minimum_required(VERSION 3.22)
project(main)

option(ENABLE_AVX OFF)
if(${ENABLE_AVX})
    add_compile_options("-mavx512f")
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)
